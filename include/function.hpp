#ifndef function_hpp
#define function_hpp

#include "node.hpp"
#include "statement.hpp"
#include <vector>
#include <iostream>
#include <string>
#include "bindings.hpp"
#include "parameter.hpp"

class Function;
typedef Node* NodePtr;

class Function : public Node{
protected:
    std::string name_;
    std::string type_;
    StatementPtr statement_;
    ParameterPtr parameter_;

public:
    Function(std::string type, std::string name, StatementPtr statement, ParameterPtr parameter = nullptr);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
};

#endif