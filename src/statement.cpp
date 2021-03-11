#include "../include/statement.hpp"

// *********** BASIC STATEMENT CLASS ************ //

Statement::Statement(StatementPtr nextStatement) : nextStatement_(nextStatement){
}

void Statement::print(){
    //TODO
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
    //TODO
}

void CompoundStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// ************ EXPRESSION STATEMENT CLASS ************ //

ExpressionStatement::ExpressionStatement(ExpressionPtr expression) : Statement(), expression_(expression) {

}

void ExpressionStatement::print(){
    //TODO
}

void ExpressionStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** IF ELSE STATEMENT CLASS ************ //

IfElseStatement::IfElseStatement(ExpressionPtr condition, StatementPtr ifStatement, StatementPtr elseStatement) : Statement(), condition_(condition), ifStatement_(ifStatement), elseStatement_(elseStatement) {

}

void IfElseStatement::print(){
    //TODO
}

void IfElseStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** ITERATION STATEMENT CLASS ************ //

IterationStatement::IterationStatement(ExpressionPtr condition, StatementPtr statement) : Statement(), condition_(condition), statement_(statement) {

}

void IterationStatement::print(){
    //TODO
}

void IterationStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** WHILE LOOP CLASS ************ //

WhileLoop::WhileLoop(ExpressionPtr condition, StatementPtr statement) : IterationStatement(condition, statement) {
    //TODO
}

void WhileLoop::print(){
    //TODO
}

void WhileLoop::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** JUMP STATEMENT CLASS ************ //

void JumpStatement::print(){
    //TODO
}

void JumpStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** RETURN STATEMENT CLASS ************ //

ReturnStatement::ReturnStatement(ExpressionPtr expression) : expression_(expression){
    //TODO
}

void ReturnStatement::print(){
    //TODO
}

void ReturnStatement::printASM(/*Bindings *bindings*/){
    //TODO
}