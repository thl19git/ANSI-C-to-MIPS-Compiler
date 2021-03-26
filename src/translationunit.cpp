#include "../include/translationunit.hpp"

TranslationUnit::TranslationUnit(NodePtr node){
    this->append(node);
}

void TranslationUnit::print(){
    for(unsigned i = 0; i < nodes_.size(); i++){
        nodes_[i]->print();
    }
}

Bindings TranslationUnit::printASM(Bindings bindings){
    for(unsigned i = 0; i < nodes_.size(); i++){
        if(nodes_[i]!=nullptr){
            bindings = nodes_[i]->printASM(bindings);
        }
    }
    return bindings;
}

void TranslationUnit::append(NodePtr node){
    nodes_.push_back(node);
}