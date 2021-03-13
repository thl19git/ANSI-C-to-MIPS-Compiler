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
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " " << op_ << " ";
    right_->print();
    std::cout << std::endl;
}

void MultiplicativeExpression::printASM(/*Bindings *bindings*/){
    //TODO
}

// *********** SHIFT EXPRESSION CLASS ************ //

ShiftExpression::ShiftExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void ShiftExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " " << op_ << " ";
    right_->print();
    std::cout << std::endl;
}

void ShiftExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** RELATIONAL EXPRESSION CLASS ************ //

RelationalExpression::RelationalExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void RelationalExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " " << op_ << " ";
    right_->print();
    std::cout << std::endl;
}

void RelationalExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** EQUALITY EXPRESSION CLASS ************ //

EqualityExpression::EqualityExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void EqualityExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " " << op_ << " ";
    right_->print();
    std::cout << std::endl;
}

void EqualityExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** LOGICAL OR EXPRESSION CLASS ************ //

LogicalOrExpression::LogicalOrExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void LogicalOrExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " || ";
    right_->print();
    std::cout << std::endl;
}

void LogicalOrExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** LOGICAL AND EXPRESSION CLASS ************ //

LogicalAndExpression::LogicalAndExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void LogicalAndExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " && ";
    right_->print();
    std::cout << std::endl;
}

void LogicalAndExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** INCLUSIVE OR EXPRESSION CLASS ************ //

InclusiveOrExpression::InclusiveOrExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void InclusiveOrExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " | ";
    right_->print();
    std::cout << std::endl;
}

void InclusiveOrExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** EXCLUSIVE OR EXPRESSION CLASS ************ //

ExclusiveOrExpression::ExclusiveOrExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void ExclusiveOrExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " ^ ";
    right_->print();
    std::cout << std::endl;
}

void ExclusiveOrExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** AND EXPRESSION CLASS ************ //

AndExpression::AndExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void AndExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    left_->print();
    std::cout << " & ";
    right_->print();
    std::cout << std::endl;
}

void AndExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** UNARY OP EXPRESSION CLASS ************ //

UnaryOpExpression::UnaryOpExpression(std::string op, ExpressionPtr unaryExpression) : op_(op), unaryExpression_(unaryExpression) {

}

void UnaryOpExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    std::cout << op_ << " ";
    unaryExpression_->print();
    std::cout << std::endl;
}

void UnaryOpExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** POSTFIX EXPRESSION CLASS ************ //

PostfixExpression::PostfixExpression(std::string op, ExpressionPtr postfixExpression) : op_(op), postfixExpression_(postfixExpression) {

}

void PostfixExpression::print(){
    if(nextExpression_!=nullptr){
        nextExpression_->print();
    }
    postfixExpression_->print();
    std::cout << op_ << std::endl;
}

void PostfixExpression::printASM(/*Bindings *bindings*/){
    //TODO
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