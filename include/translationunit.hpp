#ifndef translationunit_hpp
#define translationunit_hpp

#include "node.hpp"
#include <vector>
#include <iostream>

typedef Node* NodePtr;

class TranslationUnit : public Node{
protected:
    std::vector<NodePtr> nodes_;

public:
    TranslationUnit(NodePtr node);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
    void append(NodePtr node);
};

TranslationUnit::TranslationUnit(NodePtr node){
    this->append(node);
}

void TranslationUnit::print(){
    //std::cout << "something" << std::endl;
}

void TranslationUnit::printASM(/*Bindings *bindings*/){
    //STUFF TO ADD
    for(int i = 0; i < nodes_.size(); i++){
        nodes_[i]->printASM();
    }
}

void TranslationUnit::append(NodePtr node){
    nodes_.push_back(node);
}

#endif