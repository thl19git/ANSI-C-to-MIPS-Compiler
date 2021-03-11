#ifndef node_hpp
#define node_hpp

#include <iostream>

class Node;
typedef Node* NodePtr;

class Node {
    public:
        virtual void print() =0;
        virtual void printASM(/*Bindings *bindings*/) =0;
};

#endif