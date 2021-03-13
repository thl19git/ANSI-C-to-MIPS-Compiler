#include "../include/declaration.hpp"

// *********** BASIC DECLARATION CLASS ************ //

Declaration::Declaration(ExpressionPtr initializer) : initializer_(initializer) {

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

}

void IdentifierDeclaration::print(){
    if(nextDeclaration_!=nullptr){
        nextDeclaration_->print();
    }
    std::cout <<" " << type_ << " " << id_ << " ";
    if(initializer_!=nullptr){
        std::cout << "=";
        initializer_->print();
    }
}

void IdentifierDeclaration::printASM(/*Bindings *bindings*/){
    //TODO
}

std::string IdentifierDeclaration::getId(){
    std::cerr << "Getting declarator ID" << std::endl;
    return id_;
}