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

#endif