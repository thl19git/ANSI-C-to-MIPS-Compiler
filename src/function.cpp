#include "../include/function.hpp"

Function::Function(std::string type, std::string name, StatementPtr statement) : type_(type), name_(name), statement_(statement){

}

void Function::print(){
    std::cout << type_ << " " << name_ << "(){" << std::endl;
    statement_->print();
    std::cout << "}" << std::endl;
}

void Function::printASM(/*Bindings *bindings*/){
    //STUFF TO ADD
}