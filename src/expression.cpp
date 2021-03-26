#include "../include/expression.hpp"

// *********** BASIC EXPRESSION CLASS ************ //

void Expression::linkExpression(ExpressionPtr expression){
    nextExpression_ = expression;
}

ExpressionPtr Expression::getNext(){
    return nextExpression_;
}

std::string Expression::getId(){
    return "";
}

bool Expression::isArray(){
    return isArray_;
}

Bindings Expression::printArrayASM(Bindings bindings){
    return bindings;
}


// *********** BINARY EXPRESSION CLASS ************ //

BinaryExpression::BinaryExpression(ExpressionPtr left, ExpressionPtr right) : left_(left), right_(right){

}

void BinaryExpression::load(Bindings bindings){
    //print assembly for the left-hand side
    left_->printASM(bindings);

    //get the stack position of the left-hand side
    int leftStackPos = bindings.getTempPos();

    //increase temp position for right-hand side
    bindings.nextTempPos();

    //print assembly for the right-hand side
    right_->printASM(bindings);

    //load left hand-side into $2 ($v0)
    output << "lw $2," << leftStackPos << "($fp)" << std::endl;

    //load right hand-side into $3 ($v1)
    output << "lw $3," << bindings.getTempPos() << "($fp)" << std::endl;
}

void BinaryExpression::countTemps(int &count){
    int tmpLeft = 0, tmpRight = 0;
    left_->countTemps(tmpLeft);
    right_->countTemps(tmpRight);
    count = tmpLeft + tmpRight;
}

void BinaryExpression::countArgs(int &count){
    int tmpLeft = 0, tmpRight = 0;
    left_->countArgs(tmpLeft);
    right_->countArgs(tmpRight);
    count = std::max(tmpLeft,tmpRight);
}


// *********** UNARY EXPRESSION CLASS ************ //

UnaryExpression::UnaryExpression(/*some things*/){
    //TODO
}

void UnaryExpression::print(){
    //TODO
}

Bindings UnaryExpression::printASM(Bindings bindings){
    //TODO
    return bindings;
}


// *********** ASSIGNMENT EXPRESSION CLASS ************ //

AssignmentExpression::AssignmentExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right){

}

void AssignmentExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " = ";
    right_->print();
    std::cout << std::endl;
}

Bindings AssignmentExpression::printASM(Bindings bindings){
    
    if(!left_->isArray()){ 
        //print assembly for right-hand side, result should be in $2 and on stack
        right_->printASM(bindings);

        //increase temp stack position
        bindings.nextTempPos();

        //get left-hand side id
        std::string leftId = left_->getId();

        //get stack location of left-hand side variable
        int leftStackPos = bindings.getStackPos(leftId);

        //store $2 in location of left-hand side
        output << "sw $2," << leftStackPos << "($fp)" << std::endl;
    } else {
        //gets the right-hand side into $2 and on the stack
        right_->printASM(bindings);
        int rightpos = bindings.getTempPos();

        //increase temp stack position
        bindings.nextTempPos();

        //gets the required address into $2
        left_->printArrayASM(bindings);

        //get right-hand side into $3
        output << "lw $3," << rightpos << "($fp)" << std::endl;
        output << "nop" << std::endl;

        //store $3 in address given by $2
        output << "sw $3,0($2)" << std::endl;

    }
    return bindings;

}


// *********** CONDITIONAL EXPRESSION CLASS ************ //

ConditionalExpression::ConditionalExpression(/*some things*/){
    //TODO
}

void ConditionalExpression::print(){
    //TODO
}

Bindings ConditionalExpression::printASM(Bindings bindings){
    //TODO
    return bindings;
}


// *********** ADDITIVE EXPRESSION CLASS ************ //

AdditiveExpression::AdditiveExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op) {

}

void AdditiveExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " " << op_ << " ";
    right_->print();
    std::cout << std::endl;    
}

Bindings AdditiveExpression::printASM(Bindings bindings){
    //get left-hand side into $2 and right-hand side into $3
    load(bindings);

    //output calculation assembly
    if(op_ == "+"){
        output << "addu $2,$2,$3" << std::endl;
    } else if (op_ == "-"){
        output << "subu $2,$2,$3" << std::endl;
    }

    //store result on the stack
    output << "sw $2," << bindings.getTempPos() << "($fp)" << std::endl;

    return bindings;

}


// *********** MULTIPLICATIVE EXPRESSION CLASS ************ //

MultiplicativeExpression::MultiplicativeExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void MultiplicativeExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " " << op_ << " ";
    right_->print();
    std::cout << std::endl;
}

Bindings MultiplicativeExpression::printASM(Bindings bindings){
    //get left-hand side into $2 and right-hand side into $3
    load(bindings);

    //output calculation assembly
    if(op_ == "*"){
        output << "mul $2,$2,$3" << std::endl;
    } else if(op_ == "/" || op_ == "%"){
        output << "div $2,$3" << std::endl;
        if(op_ == "/"){
            output << "mflo $2" << std::endl;
        } else {
            output << "mfhi $2" << std::endl; 
        }
    }

    //store result on the stack
    output << "sw $2," << bindings.getTempPos() << "($fp)" << std::endl;

    return bindings;
}

// *********** SHIFT EXPRESSION CLASS ************ //

ShiftExpression::ShiftExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void ShiftExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " " << op_ << " ";
    right_->print();
    std::cout << std::endl;
}

Bindings ShiftExpression::printASM(Bindings bindings){
    //get left-hand side into $2 and right-hand side into $3
    load(bindings);

    //output calculation assembly
    if(op_ == "<<"){
        output << "sll $2,$2,$3" << std::endl;
    } else if (op_ == ">>"){
        output << "sra $2,$2,$3" << std::endl;
    }

    //store result on the stack
    output << "sw $2," << bindings.getTempPos() << "($fp)" << std::endl;

    return bindings;
}


// *********** RELATIONAL EXPRESSION CLASS ************ //

RelationalExpression::RelationalExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void RelationalExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " " << op_ << " ";
    right_->print();
    std::cout << std::endl;
}

Bindings RelationalExpression::printASM(Bindings bindings){
    //get left-hand side into $2 and right-hand side into $3
    load(bindings);

    //output calculation assembly
    if(op_ == "<"){
        output << "slt $2,$2,$3" << std::endl;
    } else if(op_ == ">"){
        output << "slt $2,$3,$2" << std::endl;
    } else if(op_ == "<="){
        output << "slt $2,$3,$2" << std::endl;
        output << "xori $2,$2,0x1" << std::endl;
    } else if(op_ == ">="){
        output << "slt $2,$2,$3" << std::endl;
        output << "xori $2,$2,0x1" << std::endl;        
    }
    output << "andi $2,$2,0x00ff" << std::endl;

    //store result on stack
    output << "sw $2," << bindings.getTempPos() << "($fp)" << std::endl;

    return bindings;
}


// *********** EQUALITY EXPRESSION CLASS ************ //

EqualityExpression::EqualityExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void EqualityExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " " << op_ << " ";
    right_->print();
    std::cout << std::endl;
}

Bindings EqualityExpression::printASM(Bindings bindings){
    //get left-hand side into $2 and right-hand side into $3
    load(bindings);

    //output calculation assembly
    output << "xor $2,$2,$3" << std::endl;
    if(op_ == "=="){
        output << "sltiu $2,$2,1" << std::endl;
    } else if (op_ == "!="){
        output << "sltu $2,$0,$2" << std::endl;
    }
    output << "andi $2,$2,0x00ff" << std::endl;

    //store result on stack
    output << "sw $2," << bindings.getTempPos() << "($fp)" << std::endl;

    return bindings;
}


// *********** LOGICAL OR EXPRESSION CLASS ************ //

LogicalOrExpression::LogicalOrExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void LogicalOrExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " || ";
    right_->print();
    std::cout << std::endl;
}

Bindings LogicalOrExpression::printASM(Bindings bindings){
    //TODO - requires a bit more thought
    return bindings;
}


// *********** LOGICAL AND EXPRESSION CLASS ************ //

LogicalAndExpression::LogicalAndExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void LogicalAndExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " && ";
    right_->print();
    std::cout << std::endl;
}

Bindings LogicalAndExpression::printASM(Bindings bindings){
    //TODO - requires a bit more thought
    return bindings;
}


// *********** INCLUSIVE OR EXPRESSION CLASS ************ //

InclusiveOrExpression::InclusiveOrExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void InclusiveOrExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " | ";
    right_->print();
    std::cout << std::endl;
}

Bindings InclusiveOrExpression::printASM(Bindings bindings){
    //get left-hand side into $2 and right-hand side into $3
    load(bindings);

    //output calculation assembly
    output << "or $2,$2,$3" << std::endl;

    //store result on stack
    output << "sw $2," << bindings.getTempPos() << "($fp)" << std::endl;

    return bindings;
}


// *********** EXCLUSIVE OR EXPRESSION CLASS ************ //

ExclusiveOrExpression::ExclusiveOrExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void ExclusiveOrExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " ^ ";
    right_->print();
    std::cout << std::endl;
}

Bindings ExclusiveOrExpression::printASM(Bindings bindings){
    //get left-hand side into $2 and right-hand side into $3
    load(bindings);

    //output calculation assembly
    output << "xor $2,$2,$3" << std::endl;

    //store result on stack
    output << "sw $2," << bindings.getTempPos() << "($fp)" << std::endl;

    return bindings;
}


// *********** AND EXPRESSION CLASS ************ //

AndExpression::AndExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void AndExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " & ";
    right_->print();
    std::cout << std::endl;
}

Bindings AndExpression::printASM(Bindings bindings){
    //get left-hand side into $2 and right-hand side into $3
    load(bindings);

    //output calculation assembly
    output << "and $2,$2,$3" << std::endl;

    //store result on stack
    output << "sw $2," << bindings.getTempPos() << "($fp)" << std::endl;

    return bindings;
}


// *********** UNARY OP EXPRESSION CLASS ************ //

UnaryOpExpression::UnaryOpExpression(std::string op, ExpressionPtr unaryExpression) : op_(op), unaryExpression_(unaryExpression) {

}

void UnaryOpExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    std::cout << op_ << " ";
    unaryExpression_->print();
    std::cout << std::endl;
}

Bindings UnaryOpExpression::printASM(Bindings bindings){
    unaryExpression_->printASM(bindings);
    if(op_ == "++"){
        output<<"addi $2,$2,1"<<std::endl;
        output<<"sw $2,"<< bindings.getStackPos(unaryExpression_->getId())<< "($fp)" <<std::endl;
    }
    //store result on the stack
    output << "sw $2," << bindings.getTempPos() << "($fp)" << std::endl;
    return bindings;
}

void UnaryOpExpression::countTemps(int &count){
    int tmp = 0;
    unaryExpression_->countTemps(tmp);
    count = tmp;
}

void UnaryOpExpression::countArgs(int &count){
    int tmp = 0;
    unaryExpression_->countArgs(tmp);
    count = tmp;
}


// *********** POSTFIX EXPRESSION CLASS ************ //

PostfixExpression::PostfixExpression(std::string op, ExpressionPtr postfixExpression) : op_(op), postfixExpression_(postfixExpression) {

}

void PostfixExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    postfixExpression_->print();
    std::cout << op_ << std::endl;
}

Bindings PostfixExpression::printASM(Bindings bindings){
    if(!postfixExpression_->isArray()){
        //get the expression into $2
        postfixExpression_->printASM(bindings);
        //store the result on the stack
        output << "sw $2," << bindings.getTempPos() << "($fp)" << std::endl;
        //add/sub one
        if(op_=="++"){
            output << "addi $2,$2,1" << std::endl;
        } else if(op_=="--"){
            output << "addiu $2,$2,-1" << std::endl;
        }
        //store the result back on stack
        output << "sw $2," << bindings.getStackPos(postfixExpression_->getId()) << "($fp)" << std::endl;
        //restore the previous value into $2
        output << "lw $2," << bindings.getTempPos() << "($fp)" << std::endl;
    } else {
        //get array address into $2
        postfixExpression_->printArrayASM(bindings);
        //load value into $3
        output << "lw $3,0($2)" << std::endl;
        //store in a temporary
        output << "sw $3," << bindings.getTempPos() << "($fp)" << std::endl;
        if(op_=="++"){
            output << "addi $3,$3,1" << std::endl;
        } else if(op_=="--"){
            output << "addiu $3,$3,-1" << std::endl;
        }
        //store the result back on stack
        output << "sw $3,0($2)" << std::endl;
        //restore the previous value into $2
        output << "lw $2," << bindings.getTempPos() << "($fp)" << std::endl;
    }
    return bindings;
}

void PostfixExpression::countTemps(int &count){
    int tmp = 0;
    postfixExpression_->countTemps(tmp);
    count = tmp;
}

void PostfixExpression::countArgs(int &count){
    int tmp = 0;
    postfixExpression_->countArgs(tmp);
    count = tmp;
}


// *********** IDENTIFIER CLASS ************ //

Identifier::Identifier(std::string id) : id_(id) {

}

void Identifier::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    std::cout << id_ << std::endl;
}

Bindings Identifier::printASM(Bindings bindings){
    //load into $2
    int stackPos = bindings.getStackPos(id_);
    output << "lw $2," << stackPos << "($fp)" << std::endl;
    output << "nop" << std::endl;

    //store on the stack
    output << "sw $2," << bindings.getTempPos() << "($fp)" << std::endl;

    return bindings;
}

void Identifier::countTemps(int &count){
    count = 1;
}

std::string Identifier::getId(){
    return id_;
}

void Identifier::countArgs(int &count){
    count = 0;
}


// *********** CONSTANT CLASS ************ //

Constant::Constant(double value) : value_(value){
    
}

void Constant::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    std::cout << " " << value_ << std::endl;
}

Bindings Constant::printASM(Bindings bindings){
    //load into $2
    output << "li $2," << value_ << std::endl;
    output << "nop" << std::endl;

    //store on the stack
    output << "sw $2," << bindings.getTempPos() << "($fp)" << std::endl;

    return bindings;
}

void Constant::countTemps(int &count){
    count = 1;
}

void Constant::countArgs(int &count){
    count = 0;
}

// *********** INITIALIZER CLASS ************ //
//possibly useless (as in not assessed)//

Initializer::Initializer(ExpressionPtr initializer) : nextInitializer_(initializer) {
}

void Initializer::print(){
    if(nextInitializer_!=nullptr){
        nextInitializer_->print();
    }
    std::cout << "Initializer" << std::endl;
}

Bindings Initializer::printASM(Bindings bindings){
    //TODO
    return bindings;
}

ExpressionPtr Initializer::getNext(){
    return nextInitializer_;
}

void Initializer::countTemps(int &count){
    count = 1; //not entirely sure what to do here
}

void Initializer::countArgs(int &count){
    count = 0; //not entirely sure what to do here
}


// *********** FUNCTION CALL CLASS ************ //

FunctionCall::FunctionCall(std::string id, InputParameterPtr params) : id_(id), parameters_(params) {

}

void FunctionCall::print(){
    std::cout << "function call" << std::endl;
}

Bindings FunctionCall::printASM(Bindings bindings){

    Bindings initialBindings = bindings;

    //count number of parameters
    int params = 0;
    if(parameters_!=nullptr){
        params = parameters_->countParams();
    }
    
    //print assembly for parameters (put on stack / in registers)
    if(params>0){
        parameters_->printParameterASM(bindings, params);
    }
    
    //jump to the function
    output << "jal " << id_ << std::endl;
    output << "nop" << std::endl;

    //result should now be in $2, so store on stack in temporary
    output << "sw $2," << bindings.getTempPos() << "($fp)" << std::endl;

    return initialBindings;
}

void FunctionCall::countTemps(int &count){
    int tmpcount = 0;
    if(parameters_!=nullptr){
        parameters_->countTemps(tmpcount);
    }
    count = tmpcount + 1;
}

void FunctionCall::countArgs(int &count){
    if(parameters_!=nullptr){
        count = parameters_->countParams();
    } else {
        count = 0;
    }
}

// *********** ARRAY EXPRESSION CLASS ************ //

ArrayExpression::ArrayExpression(std::string id, ExpressionPtr index) : id_(id), index_(index){
    isArray_ = true;
}

void ArrayExpression::print(){
    std::cout << "array expression" << std::endl;
}

Bindings ArrayExpression::printASM(Bindings bindings){

    //get correct address into $2
    printArrayASM(bindings);
    //load value at address $2 into $2
    output << "lw $2,0($2)" << std::endl;
    output << "nop" << std::endl;
    //store $2 on the stack (temporary)
    output << "sw $2," << bindings.getTempPos() << "($fp)" << std::endl;

    return bindings;
}

void ArrayExpression::countTemps(int &count){
    int tmp = 0;
    index_->countTemps(tmp);
    count = tmp;
}

void ArrayExpression::countArgs(int &count){
    int tmp = 0;
    index_->countArgs(tmp);
    count = tmp;
}

Bindings ArrayExpression::printArrayASM(Bindings bindings){
    //Evaluate index expression into $2
    index_->printASM(bindings);
    //Shift $2 left twice (multiply by 4)
    output << "sll $2,$2,2" << std::endl;
    //Get stack address
    int pos = bindings.getStackPos(id_);
    //$3 = $fp + stack address
    output << "addiu $3,$fp," << pos << std::endl;
    //$2 = $2 + $3 ($2 is now the correct address)
    output << "addu $2,$3,$2" << std::endl;

    return bindings;
}