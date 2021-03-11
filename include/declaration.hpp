#ifndef declaration_hpp
#define declaration_hpp

#include "node.hpp"
#include "expression.hpp"

class Declaration;
typedef Declaration* DeclarationPtr;

// *********** BASIC DECLARATION CLASS ************ //

class Declaration : public Node {
protected:
    ExpressionPtr initializer_;
    std::string type_;
    DeclarationPtr nextDeclaration_;

public:
    Declaration(ExpressionPtr initializer);
    virtual void print() = 0;
    virtual void printASM(/*Bindings *bindings*/) = 0;
    void linkDeclaration(DeclarationPtr declaration);
    void setType(std::string type);
    DeclarationPtr getNext();
    void setInitializer(ExpressionPtr initializer);
    virtual std::string getId() = 0;

};


// *********** IDENTIFIER DECLARATION CLASS ************ //

class IdentifierDeclaration : public Declaration {
protected:
    std::string id_;

public:
    IdentifierDeclaration(std::string id, ExpressionPtr initializer = nullptr);
    virtual void print();
    virtual void printASM(/*Bindings *bindings*/);
    virtual std::string getId();
};

#endif