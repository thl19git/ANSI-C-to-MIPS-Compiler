#ifndef statement_hpp
#define statement_hpp

#include "node.hpp"
#include "statement.hpp"
#include "declaration.hpp"
#include "expression.hpp"
#include <vector>
#include <iostream>

typedef Statement* StatementPtr;

// *********** BASIC STATEMENT CLASS ************ //

class Statement : public Node{
protected:
    StatementPtr nextStatement_;

public:
    Statement(/*some things*/);
    virtual void print() = 0;
    virtual void printASM(/*Bindings *bindings*/) = 0;
    void linkStatement(StatementPtr statement);
};


// ************ COMPOUND STATEMENT CLASS ************ //

class CompoundStatement : public Statement{
protected:
    StatementPtr statement_;
    DeclarationPtr declaration_;

public:
    CompoundStatement(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);

};


// ************ EXPRESSION STATEMENT CLASS ************ //

class ExpressionStatement : public Statement{
protected:
    ExpressionPtr expression_;

public:
    ExpressionStatement(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);

};


// *********** IF ELSE STATEMENT CLASS ************ //

class IfElseStatement : public Statement{
protected:
    ExpressionPtr condition_;
    StatementPtr ifStatement_;
    StatementPtr elseStatement;

public:
    IfElseStatement(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** ITERATION STATEMENT CLASS ************ //

class IterationStatement : public Statement{
protected:
    ExpressionPtr condition_;
    StatementPtr statement_;

public:
    IterationStatement(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** WHILE LOOP CLASS ************ //

class WhileLoop : public IterationStatement{
protected:

public:
    WhileLoop(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** JUMP STATEMENT CLASS ************ //

class JumpStatement : public Statement{
protected:

public:
    JumpStatement(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);

};


// *********** RETURN STATEMENT CLASS ************ //

class ReturnStatement : public Statement{
protected:
    ExpressionPtr expression_;

public:
    ReturnStatement(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** BASIC STATEMENT CLASS ************ //

Statement::Statement(/*some things*/){
    //TODO
}

void Statement::print(){
    //TODO
}

void Statement::printASM(/*Bindings *bindings*/){
    //TODO
}


// ************ COMPOUND STATEMENT CLASS ************ //

CompoundStatement::CompoundStatement(/*some things*/){
    //TODO
}

void CompoundStatement::print(){
    //TODO
}

void CompoundStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// ************ EXPRESSION STATEMENT CLASS ************ //

ExpressionStatement::ExpressionStatement(/*some things*/){
    //TODO
}

void ExpressionStatement::print(){
    //TODO
}

void ExpressionStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** IF ELSE STATEMENT CLASS ************ //

IfElseStatement::IfElseStatement(/*some things*/){
    //TODO
}

void IfElseStatement::print(){
    //TODO
}

void IfElseStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** ITERATION STATEMENT CLASS ************ //

IterationStatement::IterationStatement(/*some things*/){
    //TODO
}

void IterationStatement::print(){
    //TODO
}

void IterationStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** WHILE LOOP CLASS ************ //

WhileLoop::WhileLoop(/*some things*/){
    //TODO
}

void WhileLoop::print(){
    //TODO
}

void WhileLoop::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** JUMP STATEMENT CLASS ************ //

JumpStatement::JumpStatement(/*some things*/){
    //TODO
}

void JumpStatement::print(){
    //TODO
}

void JumpStatement::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** RETURN STATEMENT CLASS ************ //

ReturnStatement::ReturnStatement(/*some things*/){
    //TODO
}

void ReturnStatement::print(){
    //TODO
}

void ReturnStatement::printASM(/*Bindings *bindings*/){
    //TODO
}
#endif