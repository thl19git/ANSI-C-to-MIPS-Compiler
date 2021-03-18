#ifndef node_hpp
#define node_hpp

#include <iostream>
#include "bindings.hpp"
#include <fstream>
#include <algorithm>

extern int labelCount;
extern std::ofstream output;

class Node;
typedef Node* NodePtr;

class Node {
    public:
        virtual void print() =0;
        virtual Bindings printASM(Bindings bindings) = 0;
};

#endif