#ifndef declaration_hpp
#define declaration_hpp

#include "node.hpp"
#include "expression.hpp"
#include "block_item.hpp"
#include "bindings.hpp"

class Declaration;
typedef Declaration* DeclarationPtr;

// *********** BASIC DECLARATION CLASS ************ //

class Declaration : public BlockItem {
protected:
    ExpressionPtr initializer_;
    std::string type_;
    DeclarationPtr nextDeclaration_;

public:
    Declaration(ExpressionPtr initializer);
    virtual void print() = 0;
    virtual Bindings printASM(Bindings bindings) = 0;
    void linkDeclaration(DeclarationPtr declaration);
    void setType(std::string type);
    DeclarationPtr getNext();
    void setInitializer(ExpressionPtr initializer);
    virtual std::string getId() = 0;
    virtual void countVariables(int &count) = 0;
    virtual void countTemps(int &count) = 0;
    virtual void countArgs(int &count) = 0;

};


// *********** IDENTIFIER DECLARATION CLASS ************ //

class IdentifierDeclaration : public Declaration {
protected:
    std::string id_;

public:
    IdentifierDeclaration(std::string id, ExpressionPtr initializer = nullptr);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual std::string getId();
    virtual void countVariables(int &count);
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);
};

#endif