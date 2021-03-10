#include "../include/ast.hpp"

void parseAST();

int x;

int main(int argc, char** argv){
    // need to handle file io with input arguments bin/c_compiler -S [source-file.c] -o [dest-file.s]
    parseAST(); //currently a void function as no AST is built
}