#ifndef compiler_hpp
#define compiler_hpp

#include <string>

enum TokenType{ None, 
T_IDENTIFIER            ,
T_INT_CONST             ,
T_INT                   ,
T_IF                    ,
T_ELSE                  ,
T_WHILE                 ,
T_RETURN                ,
T_PLUS                  ,
T_ADD_ASSIGN            ,
T_MINUS                 ,
T_SUB_ASSIGN            ,
T_MULT                  ,
T_MULT_ASSIGN           ,
T_DIV                   ,
T_DIV_ASSIGN            ,
T_MOD                   ,
T_MOD_ASSIGN           	,
T_AND                   ,
T_AND_ASSIGN            ,
T_OR                    ,
T_OR_ASSIGN             ,
T_XOR                   ,
T_XOR_ASSIGN            ,
T_EQUAL                 ,
T_RSHIFT_OP             ,
T_RSHIFT_ASSIGN         ,
T_LSHIFT_OP             ,
T_LSHIFT_ASSIGN         ,
T_INC_OP                ,
T_DEC_OP                ,
T_AND_OP                ,
T_OR_OP                 ,
T_LTE_OP                ,
T_GTE_OP                ,
T_LT                    ,
T_GT                    ,
T_QUESTION             	,
T_NOT                  	,
T_INVERT               	,
T_DOT                  	,
T_EQUAL_OP     			,
T_NEQUAL_OP            	,
T_SEMICOLON            	,
T_COMMA                	,
T_COLON                	,
T_LB                   	,
T_RB                   	,
T_LCB                  	,
T_RCB                  	,
T_LSB                  	,
T_RSB                  	
};

union TokenValue{
    double numberValue;
    std::string *wordValue;
};

// This is a global variable used to move the
// attribute value from the lexer back to the
// main program.
// By convention it is called yylval, as that is
// the name that will be automatically generated
// by Bison (see next lab).
extern TokenValue yylval;

// This is the lexer function defined by flex. Each
// time it is called, a token type value will be
// returned.
extern int yylex();

#endif
