#include "../include/ast.hpp"
#include <stdio.h>
#include <iostream>
Node* parseAST();

extern void yyset_in(FILE *fd);

int x;

int main(int argc, char* argv[]){

    std::cout << "Grabbing input file" << std::endl;

    FILE* sourceFile;
    sourceFile = fopen(argv[2],"r");

    if(sourceFile==nullptr){
        throw std::runtime_error("Unable to open source file");
    }

    yyset_in(sourceFile);

    std::cout << "Lexing & parsing input, building AST" << std::endl;

    Node* ast = parseAST();

    std::cout << "Printing AST" << std::endl;

    ast->print();

    std::cout << "Printed AST, ending program" << std::endl; 
}