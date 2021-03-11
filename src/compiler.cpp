#include "../include/ast.hpp"
#include <stdio.h>
#include <iostream>
Node* parseAST();

extern void yyset_in(FILE *fd);

int x;

int main(int argc, char* argv[]){
    FILE* sourceFile;
    sourceFile = fopen(argv[2],"r");
    yyset_in(sourceFile);

    Node* ast = parseAST();
    ast->print();
}