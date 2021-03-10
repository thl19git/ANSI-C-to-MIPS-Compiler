#ifndef node_hpp
#define node_hpp

class Node {
    public:
        virtual void print() =0;
        virtual void printASM(/*Bindings *bindings*/) =0;
};

#endif