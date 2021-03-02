%option noyywrap

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */
#include "compiler.hpp"
#include <stdlib.h>
std::string* wordT = new std::string;

// This is to work around an irritating bug in Flex
// https://stackoverflow.com/questions/46213840/get-rid-of-warning-implicit-declaration-of-function-fileno-in-flex
extern "C" int fileno(FILE *stream);

/* End the embedded code section. */
%}


%%


int          { /*fprintf(stderr, "int keyword : %s\n", yytext);*/  return T_INT; }
if          { /*fprintf(stderr, "if keyword : %s\n", yytext);*/  return T_IF; }
else          { /*fprintf(stderr, "else keyword : %s\n", yytext);*/  return T_ELSE; }
while          { /*fprintf(stderr, "while keyword : %s\n", yytext);*/  return T_WHILE; }
return          { /*fprintf(stderr, "return keyword : %s\n", yytext);*/  return T_RETURN; }

"+"		{return 	T_PLUS                  	;}
"+="	{return 	T_ADD_ASSIGN            	;}
"-"		{return 	T_MINUS                 	;}
"-="	{return 	T_SUB_ASSIGN            	;}
"*"		{return 	T_MULT                  	;}
"*="	{return 	T_MULT_ASSIGN           	;}
"/"		{return 	T_DIV                   	;}
"/="	{return 	T_DIV_ASSIGN            	;}
"%"		{return 	T_MOD                   	;}
"%="	{return 	T_MOD_ASSIGN            	;}
"&"		{return 	T_AND                   	;}
"&="	{return 	T_AND_ASSIGN            	;}
"|"		{return 	T_OR                    	;}
"|="	{return 	T_OR_ASSIGN             	;}
"^"		{return 	T_XOR                   	;}
"^="	{return 	T_XOR_ASSIGN            	;}
"="		{return 	T_EQUAL                 	;}
">>"	{return 	T_RSHIFT_OP             	;}
">>="	{return 	T_RSHIFT_ASSIGN         	;}
"<<"	{return 	T_LSHIFT_OP             	;}
"<<="	{return 	T_LSHIFT_ASSIGN         	;}
"++"	{return 	T_INC_OP                	;}
"--"	{return 	T_DEC_OP                	;}
"&&"	{return 	T_AND_OP                	;}
"||"	{return 	T_OR_OP                 	;}
"<="	{return 	T_LTE_OP                	;}
">="	{return 	T_GTE_OP                	;}
"<"		{return 	T_LT                    	;}
">"		{return 	T_GT                    	;}
"?"		{return 	T_QUESTION              	;}
"!"		{return 	T_NOT                   	;}
"~"		{return 	T_INVERT                	;}
"."		{return 	T_DOT                   	;}
"=="	{return 	T_EQUAL_OP              	;}
"!="	{return 	T_NEQUAL_OP             	;}
";"		{return 	T_SEMICOLON             	;}
","		{return 	T_COMMA                 	;}
":"		{return 	T_COLON                 	;}
"("		{return 	T_LB                    	;}
")"		{return 	T_RB                    	;}
"{"		{return 	T_LCB                   	;}
"}"		{return 	T_RCB                   	;}
"["		{return 	T_LSB                   	;}
"]"		{return 	T_RSB                   	;}



[_a-zA-Z][_a-zA-Z0-9]*          { *wordT = yytext ; yylval.wordValue=wordT;  return T_IDENTIFIER; }
[0-9]+							{ yylval.numberValue=strtod(yytext,0);  return T_INT_CONST; }

\n              { /*fprintf(stderr, "Newline\n");*/ }
.				{ /*fprintf(stderr, "Unsupported character\n");*/}
%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}
//