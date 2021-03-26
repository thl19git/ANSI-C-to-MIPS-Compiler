#ifndef inputparameter_hpp
#define inputparameter_hpp

#include "node.hpp"
#include "expression.hpp"

class InputParameter;
class Expression;

typedef Expression* ExpressionPtr;

typedef InputParameter* InputParameterPtr;

class InputParameter : public Node{
protected:
    InputParameterPtr nextParameter_;
    ExpressionPtr expression_;

public:
    InputParameter(ExpressionPtr expression);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countTemps(int &count);
    void linkInputParameter(InputParameterPtr param);
    int countParams();
    void printParameterASM(Bindings bindings, int params);
};

#endif