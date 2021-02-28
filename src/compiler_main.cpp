#include "compiler.hpp"

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>

// Use a hash-table to maintain a word -> count mapping.
// This deliberately uses std::unordered_map rather than std::map,
// because we don't need to enumerate the entries in key order.
// This allows us to use a hash-table, so we get O(1) operations
// rather than O(log n).


// Define the instance of the variable that is declared in the histogram.hpp header
TokenValue yylval;
int main()
{	std::string* textString = 0;

    while(1){
        TokenType type=(TokenType)yylex();

        if(type==None){
            break; // No more tokens

        }else if(type==T_INT_CONST){
            // We have a number. The value will be
            // in yylval.numberValue
			std::cout << "Int encountered : " << yylval.numberValue << std::endl;
            // TODO: add to sum
            
        }else if(type==T_IDENTIFIER){
            // We have a string. The value is in a string
            // _pointed to_ by yylval.wordValue. Note that
            // the string is allocated by the lexer, but
            // deallocated by us.
			//std::cout << "The word is: " << *yylval.wordValue << std::endl;
            // TODO: add yylval.wordValue to histogram
			//std::cerr<<"Pointer : "<< yylval.wordValue << std::endl;
            // TODO: Free the pointer yylval.wordValue to stop leaks
			std::cout << "Identifier encountered : " << *(yylval.wordValue) << std::endl;
			
        }else{
            
            std::cerr <<"Some other token detected" << std::endl;
        }
    }
    

if(textString){delete textString;}
    return 0;
}
