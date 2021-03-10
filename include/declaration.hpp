#ifndef declaration_hpp
#define declaration_hpp

#include "node.hpp"
#include "expression.hpp"

typedef Declaration* DeclarationPtr;

// *********** BASIC DECLARATION CLASS ************ //

class Declaration : public Node {
protected:
    ExpressionPtr initializer_;
    //type
    //DeclarationPtr to next declaration?

public:
    Declaration(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);

};


// *********** IDENTIFIER DECLARATION CLASS ************ //

class IdentifierDeclaration : public Declaration {
protected:
    std::string id_;

public:
    IdentifierDeclaration(/*some things*/);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};


// *********** BASIC DECLARATION CLASS ************ //

Declaration::Declaration(/*some things*/){
    //TODO
}

void Declaration::print(){
    //TODO
}

void Declaration::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** IDENTIFIER DECLARATION CLASS ************ //

IdentifierDeclaration::IdentifierDeclaration(/*some things*/){
    //TODO
}

void IdentifierDeclaration::print(){
    //TODO
}

void IdentifierDeclaration::printASM(/*Bindings *bindings*/){
    //TODO
}
#endif