#include "../include/inputparameter.hpp"

InputParameter::InputParameter(ExpressionPtr expression) : expression_(expression){

}

void InputParameter::print(){
    std::cout << "Some input parameters" << std::endl;
}

Bindings InputParameter::printASM(Bindings bindings){
    return bindings;
}

void InputParameter::countTemps(int &count){
    if(nextParameter_!=nullptr){
        nextParameter_->countTemps(count);
    }
    expression_->countTemps(count);
}

void InputParameter::linkInputParameter(InputParameterPtr param){
    nextParameter_ = param;
}

int InputParameter::countParams(){
    if(nextParameter_!=nullptr){
        return 1 + nextParameter_->countParams();
    } else {
        return 1;
    }
}

void InputParameter::printParameterASM(Bindings bindings, int params){
    if(nextParameter_!=nullptr){
        nextParameter_->printParameterASM(bindings, params-1);
    }

    //get the expression into register $2
    expression_->printASM(bindings);

    if(params>=1 && params<=4){
        output << "move $" << params+3 << ",$2" << std::endl;
    } else{
        output << "sw $2," << (params-1)*4 << "($fp)" << std::endl;
    }

}