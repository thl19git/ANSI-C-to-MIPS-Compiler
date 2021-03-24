#include "../include/ast.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
Node* parseAST();

extern void yyset_in(FILE *fd);

std::ofstream output;
int labelCount = 0;

int main(int argc, char* argv[]){

    //std::cout << "Grabbing input file" << std::endl;

    FILE* sourceFile;

    sourceFile = fopen(argv[2],"r");

    if(sourceFile==nullptr){
        throw std::runtime_error("Unable to open source file");
    }

    output.open(argv[4]);

    if(!output.is_open()){
        throw std::runtime_error("Unable to open output file");
    }

    yyset_in(sourceFile);

    //std::cout << "Lexing & parsing input, building AST" << std::endl;

    Node* ast = parseAST();

    //std::cout << "Printing Assembly" << std::endl;

    //ast->print();

    Bindings bindings;

    try{
        bindings = ast->printASM(bindings);
    }
    catch(std::exception& e){
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    //std::cout << "Printed assembly, ending program" << std::endl;

    output.close();
}