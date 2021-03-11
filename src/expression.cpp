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
    //TODO
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
    //TODO
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
    //TODO
}

// *********** SHIFT EXPRESSION CLASS ************ //

ShiftExpression::ShiftExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void ShiftExpression::print(){
    //TODO
}

void ShiftExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** RELATIONAL EXPRESSION CLASS ************ //

RelationalExpression::RelationalExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void RelationalExpression::print(){
    //TODO
}

void RelationalExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** EQUALITY EXPRESSION CLASS ************ //

EqualityExpression::EqualityExpression(ExpressionPtr left, std::string op, ExpressionPtr right) : BinaryExpression(left, right), op_(op)  {

}

void EqualityExpression::print(){
    //TODO
}

void EqualityExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** LOGICAL OR EXPRESSION CLASS ************ //

LogicalOrExpression::LogicalOrExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void LogicalOrExpression::print(){
    //TODO
}

void LogicalOrExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** LOGICAL AND EXPRESSION CLASS ************ //

LogicalAndExpression::LogicalAndExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void LogicalAndExpression::print(){
    //TODO
}

void LogicalAndExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** INCLUSIVE OR EXPRESSION CLASS ************ //

InclusiveOrExpression::InclusiveOrExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void InclusiveOrExpression::print(){
    //TODO
}

void InclusiveOrExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** EXCLUSIVE OR EXPRESSION CLASS ************ //

ExclusiveOrExpression::ExclusiveOrExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void ExclusiveOrExpression::print(){
    //TODO
}

void ExclusiveOrExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** AND EXPRESSION CLASS ************ //

AndExpression::AndExpression(ExpressionPtr left, ExpressionPtr right) : BinaryExpression(left, right) {

}

void AndExpression::print(){
    //TODO
}

void AndExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** UNARY OP EXPRESSION CLASS ************ //

UnaryOpExpression::UnaryOpExpression(std::string op, ExpressionPtr unaryExpression) : op_(op), unaryExpression_(unaryExpression) {

}

void UnaryOpExpression::print(){
    //TODO
}

void UnaryOpExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** POSTFIX EXPRESSION CLASS ************ //

PostfixExpression::PostfixExpression(std::string op, ExpressionPtr postfixExpression) : op_(op), postfixExpression_(postfixExpression) {

}

void PostfixExpression::print(){
    //TODO
}

void PostfixExpression::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** IDENTIFIER CLASS ************ //

Identifier::Identifier(std::string id) : id_(id) {

}

void Identifier::print(){
    //TODO
}

void Identifier::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** CONSTANT CLASS ************ //

Constant::Constant(double value) : value_(value){
    
}

void Constant::print(){
    //TODO
}

void Constant::printASM(/*Bindings *bindings*/){
    //TODO
}


// *********** INITIALIZER CLASS ************ //

Initializer::Initializer(/*some things*/){
    //TODO
}

void Initializer::print(){
    //TODO
}

void Initializer::printASM(/*Bindings *bindings*/){
    //TODO
}