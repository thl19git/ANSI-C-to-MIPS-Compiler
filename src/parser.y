/*So far covers all expressions / structures in the basic feature set. Precedence and associativity is encoded in the
  grammar. */

%code requires{
  int yylex(void);
  void yyerror(const char *);
  #include <string>
  #include "../include/ast.hpp"
  #include <iostream>
  extern const Node *g_root; // A way of getting the AST out
}

%union{
  std::string *string;
  double number;
  Node* node;
  TranslationUnit* transunit;
  Function* function;
  Statement* statement;
  Expression* expression;
  Declaration* declaration;
}

%define parse.error verbose

%token T_IDENTIFIER T_INT_CONST
%token T_INT
%token T_IF T_ELSE T_WHILE T_RETURN
%token T_PLUS T_ADD_ASSIGN T_MINUS T_SUB_ASSIGN T_MULT T_MULT_ASSIGN T_DIV T_DIV_ASSIGN 
%token T_MOD T_MOD_ASSIGN T_AND T_AND_ASSIGN T_OR T_OR_ASSIGN T_XOR T_XOR_ASSIGN T_EQUAL
%token T_RSHIFT_OP T_RSHIFT_ASSIGN T_LSHIFT_OP T_LSHIFT_ASSIGN T_INC_OP T_DEC_OP T_AND_OP T_OR_OP T_LTE_OP T_GTE_OP
%token T_LT T_GT T_QUESTION T_NOT T_INVERT T_DOT T_EQUAL_OP T_NEQUAL_OP
%token T_SEMICOLON T_COMMA T_COLON
%token T_LB T_RB T_LCB T_RCB T_LSB T_RSB

%type <string> T_IDENTIFIER AssignmentOperator UnaryOperator T_INT T_INC_OP T_DEC_OP T_PLUS T_MINUS T_NOT T_INVERT T_EQUAL TypeSpecifier
               T_ADD_ASSIGN T_SUB_ASSIGN T_MULT_ASSIGN T_DIV_ASSIGN T_MOD_ASSIGN T_LSHIFT_ASSIGN T_RSHIFT_ASSIGN T_AND_ASSIGN T_OR_ASSIGN T_XOR_ASSIGN

%type <number> T_INT_CONST

%type <node> ROOT

%type <transunit> TranslationUnit

%type <function> FunctionDefinition

%type <statement> Statement StatementList IterationStatment JumpStatement ExpressionStatement SelectionStatement CompoundStatement

%type <expression> Expression PrimaryExpression PostfixExpression ConditionalExpression UnaryExpression Initializer InitializerList
                   AdditiveExpression MultiplicativeExpression ShiftExpression LogicalAndExpression LogicalOrExpression ExclusiveOrExpression
                   InclusiveOrExpression RelationalExpression AndExpression AssignmentExpression EqualityExpression

%type <declaration> Declarator Declaration DirectDeclarator DeclarationList InitDeclarator InitDeclaratorList 

%start ROOT

%%

ROOT:                   TranslationUnit {g_root = $1; std::cerr << "root = translationunit" << std::endl;} 
                        ;

TranslationUnit:        // e.g. int foo() {...}
                        FunctionDefinition {$$ = new TranslationUnit($1); std::cerr << "translationunit = function definition" << std::endl;}
                        | TranslationUnit FunctionDefinition {$$->append($2);  std::cerr << "adding function definition to translationunit" << std::endl;}
                        ;
                
FunctionDefinition:     // e.g. int foo() {...}
                        TypeSpecifier Declarator CompoundStatement {std::cerr << "trying to build a function" << std::endl; $$ = new Function(*$1,$2->getId(),$3); std::cerr << "function definition = type name compoundstatement" << std::endl;}
                        ;

CompoundStatement:      // e.g. {int x = 5; return x + 3;}
                        T_LCB T_RCB {$$ = new CompoundStatement(); std::cerr << "compound statement = {}" << std::endl;}
                        | T_LCB StatementList T_RCB {$$ = new CompoundStatement($2,NULL); std::cerr << "compound statement = {statement list}" << std::endl;}
                        | T_LCB DeclarationList T_RCB {$$ = new CompoundStatement(NULL,$2); std::cerr << "compound statement = {declaration list}" << std::endl;}
                        | T_LCB DeclarationList StatementList T_RCB {$$ = new CompoundStatement($3,$2); std::cerr << "compound statement = {declaration list, statement list}" << std::endl;}
                        ;

DeclarationList:        // e.g. int x; int y = 5;
                        Declaration {$$ = $1;}
                        | DeclarationList Declaration {$2->linkDeclaration($$); $$ = $2;  std::cerr << "adding declaration to list" << std::endl;} //may need to switch $$ and $2
                        ;

Declaration:            // e.g int x; || int x = 5;
                        TypeSpecifier InitDeclaratorList T_SEMICOLON {$$ = $2;
                                                                      Declaration* temp = $2;
                                                                      while(temp->getNext()!=nullptr){
                                                                        temp->setType(*$1);
                                                                        temp = temp->getNext();
                                                                      }
                                                                      std::cerr << "declaration = type, init declarator list" << std::endl;}
                        ;


InitDeclaratorList:     // e.g. x; || x , y || int a = 1, b = 2
                        InitDeclarator {$$ = $1; std::cerr << "init declarator list = init declarator" << std::endl;}
                        | InitDeclaratorList T_COMMA InitDeclarator {$3->linkDeclaration($$); $$ = $3; std::cerr << "adding init declarator to list" << std::endl;}
                        ;

InitDeclarator:         // e.g. a || a = 1
                        Declarator {$$ = $1;  std::cerr << "init declarator = declarator" << std::endl;}
                        | Declarator T_EQUAL Initializer {$$ = $1; $$->setInitializer($3); std::cerr << "init declarator = initialize declarator" << std::endl;}
                        ;

Declarator:             // e.g. a || sum
                        DirectDeclarator {$$ = $1; std::cerr << "declarator = direct declarator" << std::endl;}
                        ;

DirectDeclarator:       // e.g. a || sum
                        T_IDENTIFIER {$$ = new IdentifierDeclaration(*$1); std::cerr << "direct declarator = identifer" << std::endl;}
                        | T_LB Declarator T_RB {$$ = $2; std::cerr << "direct declarator = (declarator)" << std::endl;}
                        | DirectDeclarator T_LB T_RB {$$ = $1;  std::cerr << "direct declarator = direct declarator ()" << std::endl;}
                        ;
 
Initializer:            // e.g. a || b = 2
                        AssignmentExpression {$$ = $1; std::cerr << "initializer = assignment expression" << std::endl;}
                        | T_LCB InitializerList T_RCB {$$ = new Initializer($2); std::cerr << "initializer = {initializer list}" << std::endl;}
                        | T_LCB InitializerList T_COMMA T_RCB {$$ = new Initializer($2); std::cerr << "initializer = {initializer list,}" << std::endl;}
                        ;

InitializerList:        // e.g. a || a,b
                        Initializer {$$ = $1; std::cerr << "initializer list = initializer" << std::endl;}
                        | InitializerList T_COMMA Initializer {$3->linkExpression($$); $$ = $3; std::cerr << "adding initializer to list" << std::endl;}
                        ;

StatementList:          // e.g. a = 5; return a;
                        Statement {$$ = $1; std::cerr << "statement list = statement" << std::endl;}
                        | StatementList Statement {$$->linkStatement($2);  std::cerr << "adding statement to list" << std::endl;}
                        ;

Statement:              // e.g. a = 5; || return 7; || {int x = 5; return x + 3;}
                        ExpressionStatement {$$ = $1; std::cerr << "statement = expression statement" << std::endl;}
                        | SelectionStatement {$$ = $1; std::cerr << "statement = selection statement" << std::endl;}
                        | IterationStatment {$$ = $1; std::cerr << "statement = iteration statement" << std::endl;}
                        | JumpStatement {$$ = $1; std::cerr << "statement = jump statement" << std::endl;}
                        | CompoundStatement {$$ = $1; std::cerr << "statement = compound statement" << std::endl;}
                        ;

ExpressionStatement:    // e.g. a = 5; || a,b,c; || x;
                        T_SEMICOLON {$$ = new ExpressionStatement; std::cerr << "; = expression statement" << std::endl;}
                        | Expression T_SEMICOLON {$$ = new ExpressionStatement($1);  std::cerr << "expression statement" << std::endl;}
                        ;

SelectionStatement:     // e.g. if(a){...} || if(x+3) {...} else {...}
                        T_IF T_LB Expression T_RB Statement {$$ = new IfElseStatement($3,$5); std::cerr << "if statement" << std::endl;}
                        | T_IF T_LB Expression T_RB Statement T_ELSE Statement {$$ = new IfElseStatement($3,$5,$7); std::cerr << "if else statement" << std::endl;}
                        ;

IterationStatment:      // e.g. while (x > 3) {...}
                        T_WHILE T_LB Expression T_RB Statement {$$ = new WhileLoop($3,$5); std::cerr << "while loop" << std::endl;}
                        ;

JumpStatement:          // e.g. return; || return x == y;
                        T_RETURN T_SEMICOLON {$$ = new ReturnStatement; std::cerr << "return" << std::endl;}
                        | T_RETURN Expression T_SEMICOLON {$$ = new ReturnStatement($2); std::cerr << "return expression" << std::endl;}
                        ;

Expression:             // e.g. a = 5 || a,b,c || x
                        AssignmentExpression {$$ = $1; std::cerr << "expression = assignment expression" << std::endl;}
                        ;

AssignmentExpression:   // e.g. a = 5 || a += 2
                        ConditionalExpression {$$ = $1;  std::cerr << "assignment expression = conditional expression" << std::endl;}
                        | UnaryExpression AssignmentOperator AssignmentExpression {
                            if(*$2 == "="){
                              $$ = new AssignmentExpression($1,$3);
                              std::cerr << "assignment expression" << std::endl;
                            }else if(*$2 == "+="){
                              BinaryExpression* temp = new AdditiveExpression($1,"+",$3);
                              $$ = new AssignmentExpression($1,temp);
                              std::cerr << "addition assignment expression" << std::endl;
                            }else if(*$2 == "-="){
                              BinaryExpression* temp = new AdditiveExpression($1,"-",$3);
                              $$ = new AssignmentExpression($1,temp);
                              std::cerr << "subtraction assignment expression" << std::endl;
                            }else if(*$2 == "*="){
                              BinaryExpression* temp = new MultiplicativeExpression($1,"*",$3);
                              $$ = new AssignmentExpression($1,temp);
                              std::cerr << "multiplication assignment expression" << std::endl;
                            }else if(*$2 == "/="){
                              BinaryExpression* temp = new MultiplicativeExpression($1,"/",$3);
                              $$ = new AssignmentExpression($1,temp);
                              std::cerr << "division assignment expression" << std::endl;
                            }else if(*$2 == "%="){
                              BinaryExpression* temp = new MultiplicativeExpression($1,"%",$3);
                              $$ = new AssignmentExpression($1,temp);
                              std::cerr << "modulus assignment expression" << std::endl;
                            }else if(*$2 == "<<="){
                              BinaryExpression* temp = new ShiftExpression($1,"<<",$3);
                              $$ = new AssignmentExpression($1,temp);
                              std::cerr << "lshift assignment expression" << std::endl;
                            }else if(*$2 == ">>="){
                              BinaryExpression* temp = new ShiftExpression($1,">>",$3);
                              $$ = new AssignmentExpression($1,temp);
                              std::cerr << "rshift assignment expression" << std::endl;
                            }else if(*$2 == "&="){
                              BinaryExpression* temp = new AndExpression($1,$3);
                              $$ = new AssignmentExpression($1,temp);
                              std::cerr << "and assignment expression" << std::endl;
                            }else if(*$2 == "|="){
                              BinaryExpression* temp = new InclusiveOrExpression($1,$3);
                              $$ = new AssignmentExpression($1,temp);
                              std::cerr << "or assignment expression" << std::endl;
                            }else{
                              BinaryExpression* temp = new ExclusiveOrExpression($1,$3);
                              $$ = new AssignmentExpression($1,temp);
                              std::cerr << "xor assignment expression" << std::endl;
                            }}
                        ;

ConditionalExpression:  // e.g. x == y ? a = 1 : b = 3
                        LogicalOrExpression {$$ = $1; std::cerr << "conditional expression = logical or expression" << std::endl;}
                        | LogicalOrExpression T_QUESTION  Expression T_COLON ConditionalExpression {;} //TODO
                        ;

LogicalOrExpression:    // e.g. x || y
                        LogicalAndExpression {$$ = $1; std::cerr << "logical or expression = logical and expression" << std::endl;}
                        | LogicalOrExpression T_OR_OP LogicalAndExpression {$$ = new LogicalOrExpression($1,$3); std::cerr << "logical or expression" << std::endl;}
                        ;

LogicalAndExpression:   // e.g. x && y
                        InclusiveOrExpression {$$ = $1; std::cerr << "logical and expression = or expression" << std::endl;}
                        | LogicalAndExpression T_AND_OP InclusiveOrExpression {$$ = new LogicalAndExpression($1,$3); std::cerr << "logical and expression" << std::endl;}
                        ;

InclusiveOrExpression:  // e.g. x | y
                        ExclusiveOrExpression {$$ = $1; std::cerr << "or expression = xor expression" << std::endl;}
                        | InclusiveOrExpression T_OR ExclusiveOrExpression {$$ = new InclusiveOrExpression($1,$3); std::cerr << "or expression" << std::endl;}
                        ;

ExclusiveOrExpression:  // e.g. x ^ y
                        AndExpression {$$ = $1; std::cerr << "xor expression = and expression" << std::endl;}
                        | ExclusiveOrExpression T_XOR AndExpression {$$ = new ExclusiveOrExpression($1,$3); std::cerr << "xor expression" << std::endl;}
                        ;

AndExpression:          // e.g. x & y
                        EqualityExpression {$$ = $1; std::cerr << "and expression = equality expression" << std::endl;}
                        | AndExpression T_AND EqualityExpression {$$ = new AndExpression($1,$3); std::cerr << "and expression" << std::endl;}
                        ;

EqualityExpression:     // e.g. x == y || x != y
                        RelationalExpression {$$ = $1; std::cerr << "equality expression = relational expression" << std::endl;}
                        | EqualityExpression T_EQUAL_OP RelationalExpression {$$ = new EqualityExpression($1,"==",$3); std::cerr << "equal expression" << std::endl;}
                        | EqualityExpression T_NEQUAL_OP RelationalExpression {$$ = new EqualityExpression($1,"!=",$3); std::cerr << "not equal expression" << std::endl;}
                        ;

RelationalExpression:   // e.g. x > y || x <= y
                        ShiftExpression {$$ = $1; std::cerr << "relational expression = shift expression" << std::endl;}
                        | RelationalExpression T_LT ShiftExpression {$$ = new RelationalExpression($1,"<",$3); std::cerr << "lt expression" << std::endl;}
                        | RelationalExpression T_GT ShiftExpression {$$ = new RelationalExpression($1,">",$3); std::cerr << "gt expression" << std::endl;}
                        | RelationalExpression T_LTE_OP ShiftExpression {$$ = new RelationalExpression($1,"<=",$3); std::cerr << "lte expression" << std::endl;}
                        | RelationalExpression T_GTE_OP ShiftExpression {$$ = new RelationalExpression($1,">=",$3); std::cerr << "gte expression" << std::endl;}
                        ;

ShiftExpression:        // e.g. x << 2 || y >> 4
                        AdditiveExpression {$$ = $1; std::cerr << "shift expression = additive expression" << std::endl;}
                        | ShiftExpression T_LSHIFT_OP AdditiveExpression {$$ = new ShiftExpression($1,"<<",$3); std::cerr << "lshift expression" << std::endl;}
                        | ShiftExpression T_RSHIFT_OP AdditiveExpression {$$ = new ShiftExpression($1,">>",$3); std::cerr << "rshift expression" << std::endl;}
                        ;

AdditiveExpression:     // e.g. x + y || x - y
                        MultiplicativeExpression {$$ = $1; std::cerr << "additive expression = multiplicative expression" << std::endl;}
                        | AdditiveExpression T_PLUS MultiplicativeExpression {$$ = new AdditiveExpression($1,"+",$3); std::cerr << "addition expression" << std::endl;}
                        | AdditiveExpression T_MINUS MultiplicativeExpression {$$ = new AdditiveExpression($1,"-",$3); std::cerr << "subtraction expression" << std::endl;}
                        ;

MultiplicativeExpression:
                        // e.g. x * y || x / y || x % y
                        UnaryExpression {$$ = $1; std::cerr << "multiplicative expression = unary expression" << std::endl;}
                        | MultiplicativeExpression T_MULT UnaryExpression {$$ = new MultiplicativeExpression($1,"*",$3); std::cerr << "multiplication expression" << std::endl;}
                        | MultiplicativeExpression T_DIV UnaryExpression {$$ = new MultiplicativeExpression($1,"/",$3); std::cerr << "division expression" << std::endl;}
                        | MultiplicativeExpression T_MOD UnaryExpression {$$ = new MultiplicativeExpression($1,"%",$3); std::cerr << "modulus expression" << std::endl;}
                        ;

UnaryExpression:        // e.g. !x || ++y
                        PostfixExpression {$$ = $1; std::cerr << "unary expression = postfix expression" << std::endl;}
                        | UnaryOperator UnaryExpression {$$ = new UnaryOpExpression(*$1,$2); std::cerr << "UnaryOpExpression" <<  std::endl;}
                        ;

UnaryOperator:          // e.g. ++ || ! || ~
                        T_INC_OP {$$ = $1; std::cerr << "++" << std::endl;}
                        | T_DEC_OP {$$ = $1; std::cerr << "--" << std::endl;}
                        | T_PLUS {$$ = $1; std::cerr << "+" << std::endl;}
                        | T_MINUS {$$ = $1; std::cerr << "-" << std::endl;}
                        | T_NOT {$$ = $1; std::cerr << "!" << std::endl;}
                        | T_INVERT {$$ = $1; std::cerr << "~" << std::endl;}
                        ;

PrimaryExpression:      // e.g. a || 4 || ()
                        T_IDENTIFIER {$$ = new Identifier(*$1); std::cerr << "identifier" << std::endl;}
                        | T_INT_CONST {$$ = new Constant($1); std::cerr << "integer constant" << std::endl;}
                        | T_LB Expression T_RB {$$ = $2; std::cerr << "Expression in brackets" << std::endl;}
                        ;
                        

PostfixExpression:      // e.g. a++
                        PrimaryExpression {$$ = $1; std::cerr << "postfix expression = primary expression" << std::endl;}
                        | PostfixExpression T_INC_OP {$$ = new PostfixExpression("++",$1); std::cerr <<"increment operation";}
                        | PostfixExpression T_DEC_OP {$$ = new PostfixExpression("--",$1); std::cerr <<"increment operation";}
                        ;

AssignmentOperator:     // e.g +=
                        T_EQUAL {$$ = $1; std::cerr <<"="<<std::endl;}
                        | T_ADD_ASSIGN {$$ = $1; std::cerr <<"+="<<std::endl;}
                        | T_SUB_ASSIGN {$$ = $1; std::cerr <<"-="<<std::endl;}
                        | T_MULT_ASSIGN {$$ = $1; std::cerr <<"*="<<std::endl;}
                        | T_DIV_ASSIGN {$$ = $1; std::cerr <<"/="<<std::endl;}
                        | T_MOD_ASSIGN {$$ = $1; std::cerr <<"%="<<std::endl;}
                        | T_LSHIFT_ASSIGN {$$ = $1; std::cerr <<"<<="<<std::endl;}
                        | T_RSHIFT_ASSIGN {$$ = $1; std::cerr <<">>="<<std::endl;}
                        | T_AND_ASSIGN {$$ = $1; std::cerr <<"&="<<std::endl;}
                        | T_OR_ASSIGN {$$ = $1; std::cerr <<"|="<<std::endl;}
                        | T_XOR_ASSIGN {$$ = $1; std::cerr <<"^="<<std::endl;}
                        ;

TypeSpecifier:          // e.g. int
                        T_INT {$$ = $1; std::cerr << "int"<<std::endl;}
                        ;

%%


const Node *g_root; // Definition of variable (to match declaration earlier)

const Node *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
