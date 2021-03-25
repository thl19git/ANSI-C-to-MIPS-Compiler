#include "../include/function.hpp"

Function::Function(std::string type, std::string name, StatementPtr statement, ParameterPtr parameter) : name_(name), type_(type), statement_(statement), parameter_(parameter) {

}

void Function::print(){
    std::cout << type_ << " " << name_ << "(){" << std::endl;
    statement_->print();
    std::cout << "}" << std::endl;
}

Bindings Function::printASM(Bindings bindings){
    Bindings initialBindings = bindings;

    int endLabel = labelCount++;
    bindings.setFunctionEndLabel(endLabel);
    
    int variables = 0;
    statement_->countVariables(variables);
    int temporaries = 0;
    statement_->countTemps(temporaries);
    int args = 0;
    statement_->countArgs(args);

    if(args>=1 && args <=4){
        args = 4;
    }

    int stackSize = 4*(args+variables+temporaries+2); //add 2 for ra and padding

    if(stackSize%8) stackSize+= 4; //stack must be 8-byte aligned, padding at end of data section

    /* Stack Layout

        return address
        frame pointer
        variables/temporaries
        possible padding
        arguments for function calls

    */

    //directives
    output << ".globl " << name_ << std::endl;
    output << ".text" << std::endl;

    //function label
    output << name_ << ":" << std::endl;

    //decrement stack pointer
    output << "addiu $sp,$sp,-" << stackSize << std::endl;

    //store the return address
    output << "sw $31,"<< stackSize-4 << "($sp)" << std::endl;

    //store the frame pointer
    output << "sw $fp," << stackSize-8 << "($sp)" << std::endl;

    //move the stack pointer into the frame pointer
    output << "move $fp,$sp" << std::endl;

    //set stack pointer in bindings for variables
    bindings.setStackPos(args*4);

    //set stack pointer in bindings for temporaries
    bindings.setTempPos((args+variables)*4);

    //print assembly of the parameters
    if(parameter_!=nullptr){
        int num = parameter_->countParameters();
        bindings = parameter_->printParameterASM(bindings, stackSize+(num-1)*4, num);
    }

    //print assembly of the function statement
    statement_->printASM(bindings);

    //return 0 if no return statement
    output << "move $2,$0" <<std::endl;

    //label for function end
    output << "$" << endLabel << "end:" << std::endl;

    //move frame pointer into stack pointer
    output << "move $sp,$fp" << std::endl;

    //restore return address
    output << "lw $31,"<< stackSize-4 << "($sp)" << std::endl;

    //restore frame pointer
    output << "lw $fp," << stackSize-8 << "($sp)" << std::endl;

    //restore stack pointer
    output << "addiu $sp,$sp," << stackSize << std::endl;

    //jump to return address
    output << "j $31" << std::endl << "nop" << std::endl;

    return initialBindings;

}