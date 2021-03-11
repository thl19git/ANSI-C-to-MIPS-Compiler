#ifndef function_hpp
#define function_hpp

#include "node.hpp"
#include "statement.hpp"
#include <vector>
#include <iostream>
#include <string>

class Function;
typedef Node* NodePtr;

class Function : public Node{
protected:
    std::string name_;
    std::string type_;
    //some bindings??
    StatementPtr statement_;
    //some parameters

public:
    Function(std::string type, std::string name, StatementPtr statement);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};

#endif