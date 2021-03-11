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
    Statement(StatementPtr nextStatement = nullptr);
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
    CompoundStatement(StatementPtr statement);
    CompoundStatement(StatementPtr statement = nullptr, DeclarationPtr declaration = nullptr);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);

};


// ************ EXPRESSION STATEMENT CLASS ************ //

class ExpressionStatement : public Statement{
protected:
    ExpressionPtr expression_;

public:
    ExpressionStatement(ExpressionPtr expression = nullptr);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);

};


// *********** IF ELSE STATEMENT CLASS ************ //

class IfElseStatement : public Statement{
protected:
    ExpressionPtr condition_;
    StatementPtr ifStatement_;
    StatementPtr elseStatement_;

public:
    IfElseStatement(ExpressionPtr condition, StatementPtr ifStatement, StatementPtr elseStatement = nullptr);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** ITERATION STATEMENT CLASS ************ //

class IterationStatement : public Statement{
protected:
    ExpressionPtr condition_;
    StatementPtr statement_;

public:
    IterationStatement(ExpressionPtr condition, StatementPtr statement);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** WHILE LOOP CLASS ************ //

class WhileLoop : public IterationStatement{
protected:

public:
    WhileLoop(ExpressionPtr condition, StatementPtr statement);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** JUMP STATEMENT CLASS ************ //

class JumpStatement : public Statement{
protected:

public:
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);

};


// *********** RETURN STATEMENT CLASS ************ //

class ReturnStatement : public JumpStatement{
protected:
    ExpressionPtr expression_;

public:
    ReturnStatement(ExpressionPtr expression = nullptr);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};

#endif
