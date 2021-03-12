#include "../include/translationunit.hpp"

TranslationUnit::TranslationUnit(NodePtr node){
    this->append(node);
}

void TranslationUnit::print(){
    for(unsigned i = 0; i < nodes_.size(); i++){
        nodes_[i]->print();
    }
}

void TranslationUnit::printASM(/*Bindings *bindings*/){
    //STUFF TO ADD
    for(unsigned i = 0; i < nodes_.size(); i++){
        nodes_[i]->printASM();
    }
}

void TranslationUnit::append(NodePtr node){
    nodes_.push_back(node);
}