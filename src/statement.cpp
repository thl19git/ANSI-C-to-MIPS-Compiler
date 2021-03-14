#include "../include/statement.hpp"

// *********** BASIC STATEMENT CLASS ************ //

Statement::Statement(){
}

void Statement::printASM(/*Bindings *bindings*/){
    //TODO
}


// ************ COMPOUND STATEMENT CLASS ************ //

CompoundStatement::CompoundStatement(BlockItemPtr blockList) : blockList_(blockList) {

}

void CompoundStatement::print(){
    if(nextBlock_!=nullptr){
        nextBlock_->print();
    }
    if(blockList_!=nullptr){
        blockList_->print();
    }
}

void CompoundStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// ************ EXPRESSION STATEMENT CLASS ************ //

ExpressionStatement::ExpressionStatement(ExpressionPtr expression) : expression_(expression) {

}

void ExpressionStatement::print(){
    if(nextBlock_!=nullptr){
        nextBlock_->print();
    }
    expression_->print();
}

void ExpressionStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** IF ELSE STATEMENT CLASS ************ //

IfElseStatement::IfElseStatement(ExpressionPtr condition, StatementPtr ifStatement, StatementPtr elseStatement) : condition_(condition), ifStatement_(ifStatement), elseStatement_(elseStatement) {

}

void IfElseStatement::print(){
    if(nextBlock_!=nullptr){
        nextBlock_->print();
    }
    std::cout << "if(";
    condition_->print();
    std::cout << "){" << std::endl;
    ifStatement_->print();
    std::cout << "}";
    if(elseStatement_!=nullptr){
        std::cout << "else{" << std::endl;
        elseStatement_->print();
        std::cout << "}";
    }
    std::cout << std::endl;
}

void IfElseStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** ITERATION STATEMENT CLASS ************ //

IterationStatement::IterationStatement(ExpressionPtr condition, StatementPtr statement) : condition_(condition), statement_(statement) {

}

void IterationStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** WHILE LOOP CLASS ************ //

WhileLoop::WhileLoop(ExpressionPtr condition, StatementPtr statement) : IterationStatement(condition, statement) {

}

void WhileLoop::print(){
    if(nextBlock_!=nullptr){
        nextBlock_->print();
    }
    std::cout << "while(";
    condition_->print();
    std::cout << "){";
    statement_->print();
    std::cout << "}" << std::endl;
}

void WhileLoop::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** JUMP STATEMENT CLASS ************ //

void JumpStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** RETURN STATEMENT CLASS ************ //

ReturnStatement::ReturnStatement(ExpressionPtr expression) : expression_(expression){
    //TODO
}

void ReturnStatement::print(){
    if(nextBlock_!=nullptr){
        nextBlock_->print();
    }
    std::cout << "return";
    if(expression_!=nullptr){
        std::cout << " ";
        expression_->print();
        std::cout << std::endl;
    }
}

void ReturnStatement::printASM(/*Bindings *bindings*/){
    //TODO
}