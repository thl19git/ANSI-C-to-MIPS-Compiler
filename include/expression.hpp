#ifndef expression_hpp
#define expression_hpp

#include "node.hpp"
#include <string>

typedef Expression* ExpressionPtr;

// *********** BASIC EXPRESSION CLASS ************ //

class Expression : public Node {
protected:

public:
    Expression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** BINARY EXPRESSION CLASS ************ //

class BinaryExpression : public Expression {
protected:
    ExpressionPtr left_;
    ExpressionPtr right;

public:
    BinaryExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** UNARY EXPRESSION CLASS ************ //

class UnaryExpression : public Expression {
protected:

public:
    UnaryExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** ASSIGNMENT EXPRESSION CLASS ************ //

class AssignmentExpression : public BinaryExpression {
protected:
    //does this require anything?

public:
    AssignmentExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** CONDITIONAL EXPRESSION CLASS ************ //

class ConditionalExpression : public Expression {
protected:
    //needs things for turnary operator

public:
    ConditionalExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** ADDITIVE EXPRESSION CLASS ************ //

class AdditiveExpression : public BinaryExpression {
protected:
    std::string op_;
public:
    AdditiveExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** MULTIPLICATIVE EXPRESSION CLASS ************ //

class MultiplicativeExpression : public BinaryExpression {
protected:
    std::string op_;
public:
    MultiplicativeExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** SHIFT EXPRESSION CLASS ************ //

class ShiftExpression : public BinaryExpression {
protected:
    std::string op_;
public:
    ShiftExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** RELATIONAL EXPRESSION CLASS ************ //

class RelationalExpression : public BinaryExpression {
protected:
    std::string op_;
public:
    RelationalExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** EQUALITY EXPRESSION CLASS ************ //

class EqualityExpression : public BinaryExpression {
protected:
    std::string op_;
public:
    EqualityExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** LOGICAL OR EXPRESSION CLASS ************ //

class LogicalOrExpression : public BinaryExpression {
protected:

public:
    LogicalOrExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** LOGICAL AND EXPRESSION CLASS ************ //

class LogicalAndExpression : public BinaryExpression {
protected:

public:
    LogicalAndExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** INCLUSIVE OR EXPRESSION CLASS ************ //

class InclusiveOrExpression : public BinaryExpression {
protected:

public:
    InclusiveOrExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** EXCLUSIVE OR EXPRESSION CLASS ************ //

class ExclusiveOrExpression : public BinaryExpression {
protected:

public:
    ExclusiveOrExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** AND EXPRESSION CLASS ************ //

class AndExpression : public BinaryExpression {
protected:

public:
    AndExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** UNARY OP EXPRESSION CLASS ************ //

class UnaryOpExpression : public UnaryExpression {
protected:
    std::string op_;
    ExpressionPtr unaryExpression_;

public:
    UnaryOpExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** POSTFIX EXPRESSION CLASS ************ //

class PostfixExpression : public UnaryExpression {
protected:
    std::string op_;
    ExpressionPtr postfixExpression_;

public:
    PostfixExpression(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** IDENTIFIER CLASS ************ //

class Identifier : public UnaryExpression {
protected:
    std::string id_;

public:
    Identifier(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** CONSTANT CLASS ************ //

class Constant : public UnaryExpression {
protected:
    double value_;

public:
    Constant(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** INITIALIZER CLASS ************ //

class Initializer : public Expression {
protected:
    ExpressionPtr nextInitializer_; //if we care about initializer lists

public:
    Initializer(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** BASIC EXPRESSION CLASS ************ //

Expression::Expression(/*some things*/){
    //TODO
}

void Expression::print(){
    //TODO
}

void Expression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** BINARY EXPRESSION CLASS ************ //

BinaryExpression::BinaryExpression(/*some things*/){
    //TODO
}

void BinaryExpression::print(){
    //TODO
}

void BinaryExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** UNARY EXPRESSION CLASS ************ //

UnaryExpression::UnaryExpression(/*some things*/){
    //TODO
}

void UnaryExpression::print(){
    //TODO
}

void UnaryExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** ASSIGNMENT EXPRESSION CLASS ************ //

AssignmentExpression::AssignmentExpression(/*some things*/){
    //TODO
}

void AssignmentExpression::print(){
    //TODO
}

void AssignmentExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** CONDITIONAL EXPRESSION CLASS ************ //

ConditionalExpression::ConditionalExpression(/*some things*/){
    //TODO
}

void ConditionalExpression::print(){
    //TODO
}

void ConditionalExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** ADDITIVE EXPRESSION CLASS ************ //

AdditiveExpression::AdditiveExpression(/*some things*/){
    //TODO
}

void AdditiveExpression::print(){
    //TODO
}

void AdditiveExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** MULTIPLICATIVE EXPRESSION CLASS ************ //

MultiplicativeExpression::MultiplicativeExpression(/*some things*/){
    //TODO
}

void MultiplicativeExpression::print(){
    //TODO
}

void MultiplicativeExpression::printASM(/*Bindings *bindings*/){
    //TODO
}

// *********** SHIFT EXPRESSION CLASS ************ //

ShiftExpression::ShiftExpression(/*some things*/){
    //TODO
}

void ShiftExpression::print(){
    //TODO
}

void ShiftExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** RELATIONAL EXPRESSION CLASS ************ //

RelationalExpression::RelationalExpression(/*some things*/){
    //TODO
}

void RelationalExpression::print(){
    //TODO
}

void RelationalExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** EQUALITY EXPRESSION CLASS ************ //

EqualityExpression::EqualityExpression(/*some things*/){
    //TODO
}

void EqualityExpression::print(){
    //TODO
}

void EqualityExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** LOGICAL OR EXPRESSION CLASS ************ //

LogicalOrExpression::LogicalOrExpression(/*some things*/){
    //TODO
}

void LogicalOrExpression::print(){
    //TODO
}

void LogicalOrExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** LOGICAL AND EXPRESSION CLASS ************ //

LogicalAndExpression::LogicalAndExpression(/*some things*/){
    //TODO
}

void LogicalAndExpression::print(){
    //TODO
}

void LogicalAndExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** INCLUSIVE OR EXPRESSION CLASS ************ //

InclusiveOrExpression::InclusiveOrExpression(/*some things*/){
    //TODO
}

void InclusiveOrExpression::print(){
    //TODO
}

void InclusiveOrExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** EXCLUSIVE OR EXPRESSION CLASS ************ //

ExclusiveOrExpression::ExclusiveOrExpression(/*some things*/){
    //TODO
}

void ExclusiveOrExpression::print(){
    //TODO
}

void ExclusiveOrExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** AND EXPRESSION CLASS ************ //

AndExpression::AndExpression(/*some things*/){
    //TODO
}

void AndExpression::print(){
    //TODO
}

void AndExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** UNARY OP EXPRESSION CLASS ************ //

UnaryOpExpression::UnaryOpExpression(/*some things*/){
    //TODO
}

void UnaryOpExpression::print(){
    //TODO
}

void UnaryOpExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** POSTFIX EXPRESSION CLASS ************ //

PostfixExpression::PostfixExpression(/*some things*/){
    //TODO
}

void PostfixExpression::print(){
    //TODO
}

void PostfixExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** IDENTIFIER CLASS ************ //

Identifier::Identifier(/*some things*/){
    //TODO
}

void Identifier::print(){
    //TODO
}

void Identifier::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** CONSTANT CLASS ************ //

Constant::Constant(/*some things*/){
    //TODO
}

void Constant::print(){
    //TODO
}

void Constant::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** INITIALIZER CLASS ************ //

Initializer::Initializer(/*some things*/){
    //TODO
}

void Initializer::print(){
    //TODO
}

void Initializer::printASM(/*Bindings *bindings*/){
    //TODO
}
#endif