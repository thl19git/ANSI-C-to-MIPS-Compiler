#ifndef function_hpp
#define function_hpp

#include "node.hpp"
#include <vector>
#include <iostream>
#include <string>

typedef Node* NodePtr;

class Function : public Node{
protected:
    std::string name_;
    int type_;
    //some bindings??
    StatementPtr statement_;
    //some parameters

public:
    Function(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};

#endif