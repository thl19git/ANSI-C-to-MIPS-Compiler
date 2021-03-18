#ifndef translationunit_hpp
#define translationunit_hpp

#include "node.hpp"
#include <vector>
#include <iostream>
#include "bindings.hpp"

class TranslationUnit;
typedef Node* NodePtr;

class TranslationUnit : public Node{
protected:
    std::vector<NodePtr> nodes_;

public:
    TranslationUnit(NodePtr node);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    void append(NodePtr node);
};

#endif