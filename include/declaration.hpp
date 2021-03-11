#ifndef declaration_hpp
#define declaration_hpp

#include "node.hpp"
#include "expression.hpp"

typedef Declaration* DeclarationPtr;

// *********** BASIC DECLARATION CLASS ************ //

class Declaration : public Node {
protected:
    ExpressionPtr initializer_;
    std::string type_;
    DeclarationPtr nextDeclaration_;

public:
    Declaration(ExpressionPtr initializer);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
    void linkDeclaration(DeclarationPtr declaration);
    void setType(std::string type);
    DeclarationPtr getNext();
    void setInitializer(ExpressionPtr initializer);

};


// *********** IDENTIFIER DECLARATION CLASS ************ //

class IdentifierDeclaration : public Declaration {
protected:
    std::string id_;

public:
    IdentifierDeclaration(std::string id, ExpressionPtr initializer = nullptr);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
};

#endif