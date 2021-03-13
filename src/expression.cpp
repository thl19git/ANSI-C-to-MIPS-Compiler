#include "../include/expression.hpp"

// *********** BASIC EXPRESSION CLASS ************ //

void Expression::print(){
    //TODO
}

void Expression::printASM(/*Bindings *bindings*/){
    //TODO
}

void Expression::linkExpression(ExpressionPtr expression){
    nextExpression_ = expression;
}

ExpressionPtr Expression::getNext(){
    return nextExpression_;
}


// *********** BINARY EXPRESSION CLASS ************ //

BinaryExpression::BinaryExpression(ExpressionPtr left, ExpressionPtr right) : left_(left), right_(right){

}

void BinaryExpression::print(){
    //TODO
}

void BinaryExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** UNARY EXPRESSION CLASS ************ //

UnaryExpression::UnaryExpression(/*some things*/){
    //TODO
}

void UnaryExpression::print(){
    //TODO
}

void UnaryExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** ASSIGNMENT EXPRESSION CLASS ************ //

AssignmentExpression::AssignmentExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right){

}

void AssignmentExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " = ";
    right_->print();
    std::cout << std::endl;
}

void AssignmentExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** CONDITIONAL EXPRESSION CLASS ************ //

ConditionalExpression::ConditionalExpression(/*some things*/){
    //TODO
}

void ConditionalExpression::print(){
    //TODO
}

void ConditionalExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** ADDITIVE EXPRESSION CLASS ************ //

AdditiveExpression::AdditiveExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op) {

}

void AdditiveExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " " << op_ << " ";
    right_->print();
    std::cout << std::endl;    
}

void AdditiveExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** MULTIPLICATIVE EXPRESSION CLASS ************ //

MultiplicativeExpression::MultiplicativeExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void MultiplicativeExpression::print(){
    //TODO
}

void MultiplicativeExpression::printASM(/*Bindings *bindings*/){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " " << op_ << " ";
    right_->print();
    std::cout << std::endl;
}

// *********** SHIFT EXPRESSION CLASS ************ //

ShiftExpression::ShiftExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void ShiftExpression::print(){
    //TODO
}

void ShiftExpression::printASM(/*Bindings *bindings*/){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " " << op_ << " ";
    right_->print();
    std::cout << std::endl;
}


// *********** RELATIONAL EXPRESSION CLASS ************ //

RelationalExpression::RelationalExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void RelationalExpression::print(){
    //TODO
}

void RelationalExpression::printASM(/*Bindings *bindings*/){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " " << op_ << " ";
    right_->print();
    std::cout << std::endl;
}


// *********** EQUALITY EXPRESSION CLASS ************ //

EqualityExpression::EqualityExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void EqualityExpression::print(){
    //TODO
}

void EqualityExpression::printASM(/*Bindings *bindings*/){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " " << op_ << " ";
    right_->print();
    std::cout << std::endl;
}


// *********** LOGICAL OR EXPRESSION CLASS ************ //

LogicalOrExpression::LogicalOrExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void LogicalOrExpression::print(){
    //TODO
}

void LogicalOrExpression::printASM(/*Bindings *bindings*/){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " || ";
    right_->print();
    std::cout << std::endl;
}


// *********** LOGICAL AND EXPRESSION CLASS ************ //

LogicalAndExpression::LogicalAndExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void LogicalAndExpression::print(){
    //TODO
}

void LogicalAndExpression::printASM(/*Bindings *bindings*/){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " && ";
    right_->print();
    std::cout << std::endl;
}


// *********** INCLUSIVE OR EXPRESSION CLASS ************ //

InclusiveOrExpression::InclusiveOrExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void InclusiveOrExpression::print(){
    //TODO
}

void InclusiveOrExpression::printASM(/*Bindings *bindings*/){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " | ";
    right_->print();
    std::cout << std::endl;
}


// *********** EXCLUSIVE OR EXPRESSION CLASS ************ //

ExclusiveOrExpression::ExclusiveOrExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void ExclusiveOrExpression::print(){
    //TODO
}

void ExclusiveOrExpression::printASM(/*Bindings *bindings*/){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " ^ ";
    right_->print();
    std::cout << std::endl;
}


// *********** AND EXPRESSION CLASS ************ //

AndExpression::AndExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void AndExpression::print(){
    //TODO
}

void AndExpression::printASM(/*Bindings *bindings*/){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " & ";
    right_->print();
    std::cout << std::endl;
}


// *********** UNARY OP EXPRESSION CLASS ************ //

UnaryOpExpression::UnaryOpExpression(std::string op, ExpressionPtr unaryExpression) : op_(op), unaryExpression_(unaryExpression) {

}

void UnaryOpExpression::print(){
    //TODO
}

void UnaryOpExpression::printASM(/*Bindings *bindings*/){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    std::cout << op_ << " ";
    unaryExpression_->print();
    std::cout << std::endl;
}


// *********** POSTFIX EXPRESSION CLASS ************ //

PostfixExpression::PostfixExpression(std::string op, ExpressionPtr postfixExpression) : op_(op), postfixExpression_(postfixExpression) {

}

void PostfixExpression::print(){
    //TODO
}

void PostfixExpression::printASM(/*Bindings *bindings*/){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    postfixExpression_->print();
    std::cout << op_ << std::endl;
}


// *********** IDENTIFIER CLASS ************ //

Identifier::Identifier(std::string id) : id_(id) {

}

void Identifier::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    std::cout << id_ << std::endl;
}

void Identifier::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** CONSTANT CLASS ************ //

Constant::Constant(double value) : value_(value){
    
}

void Constant::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    std::cout << " " << value_ << std::endl;
}

void Constant::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** INITIALIZER CLASS ************ //

Initializer::Initializer(ExpressionPtr initializer) : nextInitializer_(initializer) {
}

void Initializer::print(){
    if(nextInitializer_!=nullptr){
        nextInitializer_->print();
    }
    std::cout << "Initializer" << std::endl;
}

void Initializer::printASM(/*Bindings *bindings*/){
    //TODO
}

ExpressionPtr Initializer::getNext(){
    return nextInitializer_;
}