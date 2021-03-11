#include "../include/declaration.hpp"

// *********** BASIC DECLARATION CLASS ************ //

Declaration::Declaration(ExpressionPtr initializer) : initializer_(initializer) {

}

void Declaration::print(){
    //TODO
}

void Declaration::printASM(/*Bindings *bindings*/){
    //TODO
}

void Declaration::linkDeclaration(DeclarationPtr declaration){
    nextDeclaration_ = declaration;
}

void Declaration::setType(std::string type){
    type_ = type;
}

DeclarationPtr Declaration::getNext(){
    return nextDeclaration_;
}

void Declaration::setInitializer(ExpressionPtr initializer){
    initializer_ = initializer;
}


// *********** IDENTIFIER DECLARATION CLASS ************ //

IdentifierDeclaration::IdentifierDeclaration(std::string id, ExpressionPtr initializer) : Declaration(initializer), id_(id){
    //TODO
}

void IdentifierDeclaration::print(){
    //TODO
}

void IdentifierDeclaration::printASM(/*Bindings *bindings*/){
    //TODO
}