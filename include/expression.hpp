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
    ExpressionPtr right_;

public:
    BinaryExpression(ExpressionPtr left, ExpressionPtr right);
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
    AssignmentExpression(ExpressionPtr left, ExpressionPtr right);
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
    AdditiveExpression(ExpressionPtr left, std::string op, ExpressionPtr right);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** MULTIPLICATIVE EXPRESSION CLASS ************ //

class MultiplicativeExpression : public BinaryExpression {
protected:
    std::string op_;
public:
    MultiplicativeExpression(ExpressionPtr left, std::string op, ExpressionPtr right);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** SHIFT EXPRESSION CLASS ************ //

class ShiftExpression : public BinaryExpression {
protected:
    std::string op_;
public:
    ShiftExpression(ExpressionPtr left, std::string op, ExpressionPtr right);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** RELATIONAL EXPRESSION CLASS ************ //

class RelationalExpression : public BinaryExpression {
protected:
    std::string op_;
public:
    RelationalExpression(ExpressionPtr left, std::string op, ExpressionPtr right);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** EQUALITY EXPRESSION CLASS ************ //

class EqualityExpression : public BinaryExpression {
protected:
    std::string op_;
public:
    EqualityExpression(ExpressionPtr left, std::string op, ExpressionPtr right);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** LOGICAL OR EXPRESSION CLASS ************ //

class LogicalOrExpression : public BinaryExpression {
protected:

public:
    LogicalOrExpression(ExpressionPtr left, ExpressionPtr right);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** LOGICAL AND EXPRESSION CLASS ************ //

class LogicalAndExpression : public BinaryExpression {
protected:

public:
    LogicalAndExpression(ExpressionPtr left, ExpressionPtr right);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** INCLUSIVE OR EXPRESSION CLASS ************ //

class InclusiveOrExpression : public BinaryExpression {
protected:

public:
    InclusiveOrExpression(ExpressionPtr left, ExpressionPtr right);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** EXCLUSIVE OR EXPRESSION CLASS ************ //

class ExclusiveOrExpression : public BinaryExpression {
protected:

public:
    ExclusiveOrExpression(ExpressionPtr left, ExpressionPtr right);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** AND EXPRESSION CLASS ************ //

class AndExpression : public BinaryExpression {
protected:

public:
    AndExpression(ExpressionPtr left, ExpressionPtr right);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** UNARY OP EXPRESSION CLASS ************ //

class UnaryOpExpression : public UnaryExpression {
protected:
    std::string op_;
    ExpressionPtr unaryExpression_;

public:
    UnaryOpExpression(std::string op, ExpressionPtr unaryExpression);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** POSTFIX EXPRESSION CLASS ************ //

class PostfixExpression : public UnaryExpression {
protected:
    std::string op_;
    ExpressionPtr postfixExpression_;

public:
    PostfixExpression(std::string op, ExpressionPtr postfixExpression);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** IDENTIFIER CLASS ************ //

class Identifier : public UnaryExpression {
protected:
    std::string id_;

public:
    Identifier(std::string id);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** CONSTANT CLASS ************ //

class Constant : public UnaryExpression {
protected:
    double value_;

public:
    Constant(double value);
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

BinaryExpression::BinaryExpression(ExpressionPtr left, ExpressionPtr right) : left_(left), right_(right){

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

AssignmentExpression::AssignmentExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right){

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

AdditiveExpression::AdditiveExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op) {

}

void AdditiveExpression::print(){
    //TODO
}

void AdditiveExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** MULTIPLICATIVE EXPRESSION CLASS ************ //

MultiplicativeExpression::MultiplicativeExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void MultiplicativeExpression::print(){
    //TODO
}

void MultiplicativeExpression::printASM(/*Bindings *bindings*/){
    //TODO
}

// *********** SHIFT EXPRESSION CLASS ************ //

ShiftExpression::ShiftExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void ShiftExpression::print(){
    //TODO
}

void ShiftExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** RELATIONAL EXPRESSION CLASS ************ //

RelationalExpression::RelationalExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void RelationalExpression::print(){
    //TODO
}

void RelationalExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** EQUALITY EXPRESSION CLASS ************ //

EqualityExpression::EqualityExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void EqualityExpression::print(){
    //TODO
}

void EqualityExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** LOGICAL OR EXPRESSION CLASS ************ //

LogicalOrExpression::LogicalOrExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void LogicalOrExpression::print(){
    //TODO
}

void LogicalOrExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** LOGICAL AND EXPRESSION CLASS ************ //

LogicalAndExpression::LogicalAndExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void LogicalAndExpression::print(){
    //TODO
}

void LogicalAndExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** INCLUSIVE OR EXPRESSION CLASS ************ //

InclusiveOrExpression::InclusiveOrExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void InclusiveOrExpression::print(){
    //TODO
}

void InclusiveOrExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** EXCLUSIVE OR EXPRESSION CLASS ************ //

ExclusiveOrExpression::ExclusiveOrExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void ExclusiveOrExpression::print(){
    //TODO
}

void ExclusiveOrExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** AND EXPRESSION CLASS ************ //

AndExpression::AndExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void AndExpression::print(){
    //TODO
}

void AndExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** UNARY OP EXPRESSION CLASS ************ //

UnaryOpExpression::UnaryOpExpression(std::string op, ExpressionPtr unaryExpression) : op_(op), unaryExpression_(unaryExpression) {

}

void UnaryOpExpression::print(){
    //TODO
}

void UnaryOpExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** POSTFIX EXPRESSION CLASS ************ //

PostfixExpression::PostfixExpression(std::string op, ExpressionPtr postfixExpression) : op_(op), postfixExpression_(postfixExpression) {

}

void PostfixExpression::print(){
    //TODO
}

void PostfixExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** IDENTIFIER CLASS ************ //

Identifier::Identifier(std::string id) : id_(id) {

}

void Identifier::print(){
    //TODO
}

void Identifier::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** CONSTANT CLASS ************ //

Constant::Constant(double value) : value_(value){
    
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