#ifndef expression_hpp
#define expression_hpp

#include "node.hpp"
#include <string>
#include "bindings.hpp"
#include "inputparameter.hpp"

class Expression;
class InputParameter;
typedef InputParameter* InputParameterPtr;
typedef Expression* ExpressionPtr;

// *********** BASIC EXPRESSION CLASS ************ //

class Expression : public Node {
protected:
    ExpressionPtr nextExpression_; //only required for initializer lists which we aren't tested on
    bool isArray_ = false;
public:
    virtual void print() = 0;
    virtual Bindings printASM(Bindings bindings) = 0;
    void linkExpression(ExpressionPtr expression);
    ExpressionPtr getNext();
    virtual void countTemps(int &count) = 0;
    virtual std::string getId();
    virtual void countArgs(int &count) = 0;
    bool isArray();
    virtual Bindings printArrayASM(Bindings bindings);
};


// *********** BINARY EXPRESSION CLASS ************ //

class BinaryExpression : public Expression {
protected:
    ExpressionPtr left_;
    ExpressionPtr right_;

public:
    BinaryExpression(ExpressionPtr left, ExpressionPtr right);
    virtual void print() = 0;
    virtual Bindings printASM(Bindings bindings) = 0;
    virtual void countTemps(int &count);
    void load(Bindings bindings);
    virtual void countArgs(int &count);
};


// *********** UNARY EXPRESSION CLASS ************ //

class UnaryExpression : public Expression {
protected:

public:
    UnaryExpression(/*some things*/);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countTemps(int &count) = 0;
    virtual void countArgs(int &count) = 0;
};


// *********** ASSIGNMENT EXPRESSION CLASS ************ //

class AssignmentExpression : public BinaryExpression {
protected:
    //does this require anything?

public:
    AssignmentExpression(ExpressionPtr left, ExpressionPtr right);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
};


// *********** CONDITIONAL EXPRESSION CLASS ************ //

class ConditionalExpression : public Expression {
protected:
    //needs things for turnary operator

public:
    ConditionalExpression(/*some things*/);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
};


// *********** ADDITIVE EXPRESSION CLASS ************ //

class AdditiveExpression : public BinaryExpression {
protected:
    std::string op_;
public:
    AdditiveExpression(ExpressionPtr left, std::string op, ExpressionPtr right);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
};


// *********** MULTIPLICATIVE EXPRESSION CLASS ************ //

class MultiplicativeExpression : public BinaryExpression {
protected:
    std::string op_;
public:
    MultiplicativeExpression(ExpressionPtr left, std::string op, ExpressionPtr right);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
};


// *********** SHIFT EXPRESSION CLASS ************ //

class ShiftExpression : public BinaryExpression {
protected:
    std::string op_;
public:
    ShiftExpression(ExpressionPtr left, std::string op, ExpressionPtr right);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
};


// *********** RELATIONAL EXPRESSION CLASS ************ //

class RelationalExpression : public BinaryExpression {
protected:
    std::string op_;
public:
    RelationalExpression(ExpressionPtr left, std::string op, ExpressionPtr right);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
};


// *********** EQUALITY EXPRESSION CLASS ************ //

class EqualityExpression : public BinaryExpression {
protected:
    std::string op_;
public:
    EqualityExpression(ExpressionPtr left, std::string op, ExpressionPtr right);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
};


// *********** LOGICAL OR EXPRESSION CLASS ************ //

class LogicalOrExpression : public BinaryExpression {
protected:

public:
    LogicalOrExpression(ExpressionPtr left, ExpressionPtr right);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
};


// *********** LOGICAL AND EXPRESSION CLASS ************ //

class LogicalAndExpression : public BinaryExpression {
protected:

public:
    LogicalAndExpression(ExpressionPtr left, ExpressionPtr right);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
};


// *********** INCLUSIVE OR EXPRESSION CLASS ************ //

class InclusiveOrExpression : public BinaryExpression {
protected:

public:
    InclusiveOrExpression(ExpressionPtr left, ExpressionPtr right);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
};


// *********** EXCLUSIVE OR EXPRESSION CLASS ************ //

class ExclusiveOrExpression : public BinaryExpression {
protected:

public:
    ExclusiveOrExpression(ExpressionPtr left, ExpressionPtr right);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
};


// *********** AND EXPRESSION CLASS ************ //

class AndExpression : public BinaryExpression {
protected:

public:
    AndExpression(ExpressionPtr left, ExpressionPtr right);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
};


// *********** UNARY OP EXPRESSION CLASS ************ //

class UnaryOpExpression : public UnaryExpression {
protected:
    std::string op_;
    ExpressionPtr unaryExpression_;

public:
    UnaryOpExpression(std::string op, ExpressionPtr unaryExpression);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);
};


// *********** POSTFIX EXPRESSION CLASS ************ //

class PostfixExpression : public UnaryExpression {
protected:
    std::string op_;
    ExpressionPtr postfixExpression_;

public:
    PostfixExpression(std::string op, ExpressionPtr postfixExpression);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);
};


// *********** IDENTIFIER CLASS ************ //

class Identifier : public UnaryExpression {
protected:
    std::string id_;

public:
    Identifier(std::string id);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countTemps(int &count);
    virtual std::string getId();
    virtual void countArgs(int &count);
};


// *********** CONSTANT CLASS ************ //

class Constant : public UnaryExpression {
protected:
    double value_;

public:
    Constant(double value);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);
};


// *********** INITIALIZER CLASS ************ //

class Initializer : public Expression {
protected:
    ExpressionPtr nextInitializer_; //if we care about initializer lists

public:
    Initializer(ExpressionPtr initializer);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    ExpressionPtr getNext();
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);
};

// *********** FUNCTION CALL CLASS ************ //

class FunctionCall : public Expression {
protected:
    std::string id_;
    InputParameterPtr parameters_;

public:
    FunctionCall(std::string id, InputParameterPtr params = nullptr);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);
};


// *********** ARRAY EXPRESSION CLASS ************ //

class ArrayExpression : public UnaryExpression {
protected:
    std::string id_;
    ExpressionPtr index_;

public:
    ArrayExpression(std::string id, ExpressionPtr index);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);
    virtual Bindings printArrayASM(Bindings bindings);
};


#endif