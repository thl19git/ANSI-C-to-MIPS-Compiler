#include "../include/statement.hpp"

// *********** BASIC STATEMENT CLASS ************ //

Statement::Statement(StatementPtr nextStatement) : nextStatement_(nextStatement){
}

void Statement::printASM(/*Bindings *bindings*/){
    //TODO
}

void Statement::linkStatement(StatementPtr statement){
    nextStatement_ = statement;
}


// ************ COMPOUND STATEMENT CLASS ************ //

CompoundStatement::CompoundStatement(StatementPtr statement) : Statement(), statement_(statement) {

}

CompoundStatement::CompoundStatement(StatementPtr statement, DeclarationPtr declaration) : Statement(), statement_(statement), declaration_(declaration) {

}

void CompoundStatement::print(){
    if(nextStatement_!=nullptr){
        nextStatement_->print();
    }
    
    if(declaration_!=nullptr){
        declaration_->print();
    }
    
    if(statement_!=nullptr){
        statement_->print();
    }
}

void CompoundStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// ************ EXPRESSION STATEMENT CLASS ************ //

ExpressionStatement::ExpressionStatement(ExpressionPtr expression) : Statement(), expression_(expression) {

}

void ExpressionStatement::print(){
    if(nextStatement_!=nullptr){
        nextStatement_->print();
    }
    expression_->print();
}

void ExpressionStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** IF ELSE STATEMENT CLASS ************ //

IfElseStatement::IfElseStatement(ExpressionPtr condition, StatementPtr ifStatement, StatementPtr elseStatement) : Statement(), condition_(condition), ifStatement_(ifStatement), elseStatement_(elseStatement) {

}

void IfElseStatement::print(){
    if(nextStatement_!=nullptr){
        nextStatement_->print();
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

IterationStatement::IterationStatement(ExpressionPtr condition, StatementPtr statement) : Statement(), condition_(condition), statement_(statement) {

}

void IterationStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** WHILE LOOP CLASS ************ //

WhileLoop::WhileLoop(ExpressionPtr condition, StatementPtr statement) : IterationStatement(condition, statement) {

}

void WhileLoop::print(){
    if(nextStatement_!=nullptr){
        nextStatement_->print();
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
    if(nextStatement_!=nullptr){
        nextStatement_->print();
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