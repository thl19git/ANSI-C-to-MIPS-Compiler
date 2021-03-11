/*So far covers all expressions / structures in the basic feature set. Precedence and associativity is encoded in the
  grammar. */

%code requires{
  int yylex(void);
  void yyerror(const char *);
  #include <string>
  #include "../include/ast.hpp"
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

ROOT:                   TranslationUnit {g_root = $1;}
                        ;

TranslationUnit:        // e.g. int foo() {...}
                        FunctionDefinition {$$ = new TranslationUnit($1);}
                        | TranslationUnit FunctionDefinition {$$->append($2);}
                        ;
                
FunctionDefinition:     // e.g. int foo() {...}
                        TypeSpecifier Declarator CompoundStatement {$$ = new Function(*$1,$2->getId(),$3);}
                        ;

CompoundStatement:      // e.g. {int x = 5; return x + 3;}
                        T_LCB T_RCB {$$ = new CompoundStatement();}
                        | T_LCB StatementList T_RCB {$$ = new CompoundStatement($2,NULL);}
                        | T_LCB DeclarationList T_RCB {$$ = new CompoundStatement(NULL,$2);}
                        | T_LCB DeclarationList StatementList T_RCB {$$ = new CompoundStatement($3,$2);}
                        ;

DeclarationList:        // e.g. int x; int y = 5;
                        Declaration {$$ = $1;}
                        | DeclarationList Declaration {$2->linkDeclaration($$); $$ = $2;}
                        ;

Declaration:            // e.g int x; || int x = 5;
                        TypeSpecifier InitDeclaratorList T_SEMICOLON {$$ = $2;
                                                                      Declaration* temp = $2;
                                                                      while(temp->getNext()!=nullptr){
                                                                        temp->setType(*$1);
                                                                        temp = temp->getNext();
                                                                      }}
                        ;


InitDeclaratorList:     // e.g. x; || x , y || int a = 1, b = 2
                        InitDeclarator {$$ = $1;}
                        | InitDeclaratorList T_COMMA InitDeclarator {$3->linkDeclaration($$); $$ = $3;}
                        ;

InitDeclarator:         // e.g. a || a = 1
                        Declarator {$$ = $1;}
                        | Declarator T_EQUAL Initializer {$$ = $1; $$->setInitializer($3);}
                        ;

Declarator:             // e.g. a || sum
                        DirectDeclarator {$$ = $1;}
                        ;

DirectDeclarator:       // e.g. a || sum
                        T_IDENTIFIER {$$ = new IdentifierDeclaration(*$1);}
                        | T_LB Declarator T_RB {$$ = $2;}
                        | DirectDeclarator T_LB T_RB {;} //TODO
                        ;
 
Initializer:            // e.g. a || b = 2
                        AssignmentExpression {$$ = $1;}
                        | T_LCB InitializerList T_RCB {$$ = new Initializer($2);}
                        | T_LCB InitializerList T_COMMA T_RCB {$$ = new Initializer($2);}
                        ;

InitializerList:        // e.g. a || a,b
                        Initializer {$$ = $1;}
                        | InitializerList T_COMMA Initializer {$3->linkExpression($$); $$ = $3;}
                        ;

StatementList:          // e.g. a = 5; return a;
                        Statement {$$ = $1;}
                        | StatementList Statement {$$->linkStatement($2);}
                        ;

Statement:              // e.g. a = 5; || return 7; || {int x = 5; return x + 3;}
                        ExpressionStatement {$$ = $1;}
                        | SelectionStatement {$$ = $1;}
                        | IterationStatment {$$ = $1;}
                        | JumpStatement {$$ = $1;}
                        | CompoundStatement {$$ = $1;}
                        ;

ExpressionStatement:    // e.g. a = 5; || a,b,c; || x;
                        T_SEMICOLON {$$ = new ExpressionStatement;}
                        | Expression T_SEMICOLON {$$ = new ExpressionStatement($1);}
                        ;

SelectionStatement:     // e.g. if(a){...} || if(x+3) {...} else {...}
                        T_IF T_LB Expression T_RB Statement {$$ = new IfElseStatement($3,$5);}
                        | T_IF T_LB Expression T_RB Statement T_ELSE Statement {$$ = new IfElseStatement($3,$5,$7);}
                        ;

IterationStatment:      // e.g. while (x > 3) {...}
                        T_WHILE T_LB Expression T_RB Statement {$$ = new WhileLoop($3,$5);}
                        ;

JumpStatement:          // e.g. return; || return x == y;
                        T_RETURN T_SEMICOLON {$$ = new ReturnStatement;}
                        | T_RETURN Expression T_SEMICOLON {$$ = new ReturnStatement($2);}
                        ;

Expression:             // e.g. a = 5 || a,b,c || x
                        AssignmentExpression {$$ = $1;}
                        ;

AssignmentExpression:   // e.g. a = 5 || a += 2
                        ConditionalExpression {$$ = $1;}
                        | UnaryExpression AssignmentOperator AssignmentExpression {
                            if(*$2 == "="){
                              $$ = new AssignmentExpression($1,$3);
                            }else if(*$2 == "+="){
                              BinaryExpression* temp = new AdditiveExpression($1,"+",$3);
                              $$ = new AssignmentExpression($1,temp);
                            }else if(*$2 == "-="){
                              BinaryExpression* temp = new AdditiveExpression($1,"-",$3);
                              $$ = new AssignmentExpression($1,temp);
                            }else if(*$2 == "*="){
                              BinaryExpression* temp = new MultiplicativeExpression($1,"*",$3);
                              $$ = new AssignmentExpression($1,temp);
                            }else if(*$2 == "/="){
                              BinaryExpression* temp = new MultiplicativeExpression($1,"/",$3);
                              $$ = new AssignmentExpression($1,temp);
                            }else if(*$2 == "%="){
                              BinaryExpression* temp = new MultiplicativeExpression($1,"%",$3);
                              $$ = new AssignmentExpression($1,temp);
                            }else if(*$2 == "<<="){
                              BinaryExpression* temp = new ShiftExpression($1,"<<",$3);
                              $$ = new AssignmentExpression($1,temp);
                            }else if(*$2 == ">>="){
                              BinaryExpression* temp = new ShiftExpression($1,">>",$3);
                              $$ = new AssignmentExpression($1,temp);
                            }else if(*$2 == "&="){
                              BinaryExpression* temp = new AndExpression($1,$3);
                              $$ = new AssignmentExpression($1,temp);
                            }else if(*$2 == "|="){
                              BinaryExpression* temp = new InclusiveOrExpression($1,$3);
                              $$ = new AssignmentExpression($1,temp);
                            }else{
                              BinaryExpression* temp = new ExclusiveOrExpression($1,$3);
                              $$ = new AssignmentExpression($1,temp);
                            }}
                        ;

ConditionalExpression:  // e.g. x == y ? a = 1 : b = 3
                        LogicalOrExpression {$$ = $1;}
                        | LogicalOrExpression T_QUESTION  Expression T_COLON ConditionalExpression {;} //TODO
                        ;

LogicalOrExpression:    // e.g. x || y
                        LogicalAndExpression {$$ = $1;}
                        | LogicalOrExpression T_OR_OP LogicalAndExpression {$$ = new LogicalOrExpression($1,$3);}
                        ;

LogicalAndExpression:   // e.g. x && y
                        InclusiveOrExpression {$$ = $1;}
                        | LogicalAndExpression T_AND_OP InclusiveOrExpression {$$ = new LogicalAndExpression($1,$3);}
                        ;

InclusiveOrExpression:  // e.g. x | y
                        ExclusiveOrExpression {$$ = $1;}
                        | InclusiveOrExpression T_OR ExclusiveOrExpression {$$ = new InclusiveOrExpression($1,$3);}
                        ;

ExclusiveOrExpression:  // e.g. x ^ y
                        AndExpression {$$ = $1;}
                        | ExclusiveOrExpression T_XOR AndExpression {$$ = new ExclusiveOrExpression($1,$3);}
                        ;

AndExpression:          // e.g. x & y
                        EqualityExpression {$$ = $1;}
                        | AndExpression T_AND EqualityExpression {$$ = new AndExpression($1,$3);}
                        ;

EqualityExpression:     // e.g. x == y || x != y
                        RelationalExpression {$$ = $1;}
                        | EqualityExpression T_EQUAL_OP RelationalExpression {$$ = new EqualityExpression($1,"==",$3);}
                        | EqualityExpression T_NEQUAL_OP RelationalExpression {$$ = new EqualityExpression($1,"!=",$3);}
                        ;

RelationalExpression:   // e.g. x > y || x <= y
                        ShiftExpression {$$ = $1;}
                        | RelationalExpression T_LT ShiftExpression {$$ = new RelationalExpression($1,"<",$3);}
                        | RelationalExpression T_GT ShiftExpression {$$ = new RelationalExpression($1,">",$3);}
                        | RelationalExpression T_LTE_OP ShiftExpression {$$ = new RelationalExpression($1,"<=",$3);}
                        | RelationalExpression T_GTE_OP ShiftExpression {$$ = new RelationalExpression($1,">=",$3);}
                        ;

ShiftExpression:        // e.g. x << 2 || y >> 4
                        AdditiveExpression {$$ = $1;}
                        | ShiftExpression T_LSHIFT_OP AdditiveExpression {$$ = new ShiftExpression($1,"<<",$3);}
                        | ShiftExpression T_RSHIFT_OP AdditiveExpression {$$ = new ShiftExpression($1,">>",$3);}
                        ;

AdditiveExpression:     // e.g. x + y || x - y
                        MultiplicativeExpression {$$ = $1;}
                        | AdditiveExpression T_PLUS MultiplicativeExpression {$$ = new AdditiveExpression($1,"+",$3);}
                        | AdditiveExpression T_MINUS MultiplicativeExpression {$$ = new AdditiveExpression($1,"-",$3);}
                        ;

MultiplicativeExpression:
                        // e.g. x * y || x / y || x % y
                        UnaryExpression {$$ = $1;}
                        | MultiplicativeExpression T_MULT UnaryExpression {$$ = new MultiplicativeExpression($1,"*",$3);}
                        | MultiplicativeExpression T_DIV UnaryExpression {$$ = new MultiplicativeExpression($1,"/",$3);}
                        | MultiplicativeExpression T_MOD UnaryExpression {$$ = new MultiplicativeExpression($1,"%",$3);}
                        ;

UnaryExpression:        // e.g. !x || ++y
                        PostfixExpression {$$ = $1;}
                        | UnaryOperator UnaryExpression {$$ = new UnaryOpExpression(*$1,$2);}
                        ;

UnaryOperator:          // e.g. ++ || ! || ~
                        T_INC_OP {$$ = $1;}
                        | T_DEC_OP {$$ = $1;}
                        | T_PLUS {$$ = $1;}
                        | T_MINUS {$$ = $1;}
                        | T_NOT {$$ = $1;}
                        | T_INVERT {$$ = $1;}
                        ;

PrimaryExpression:      // e.g. a || 4 || ()
                        T_IDENTIFIER {$$ = new Identifier(*$1);}
                        | T_INT_CONST {$$ = new Constant($1);}
                        | T_LB Expression T_RB {$$ = $2;}
                        ;
                        

PostfixExpression:      // e.g. a++
                        PrimaryExpression {$$ = $1;}
                        | PostfixExpression T_INC_OP {$$ = new PostfixExpression("++",$1);}
                        | PostfixExpression T_DEC_OP {$$ = new PostfixExpression("--",$1);}
                        ;

AssignmentOperator:     // e.g +=
                        T_EQUAL {$$ = $1;}
                        | T_ADD_ASSIGN {$$ = $1;}
                        | T_SUB_ASSIGN {$$ = $1;}
                        | T_MULT_ASSIGN {$$ = $1;}
                        | T_DIV_ASSIGN {$$ = $1;}
                        | T_MOD_ASSIGN {$$ = $1;}
                        | T_LSHIFT_ASSIGN {$$ = $1;}
                        | T_RSHIFT_ASSIGN {$$ = $1;}
                        | T_AND_ASSIGN {$$ = $1;}
                        | T_OR_ASSIGN {$$ = $1;}
                        | T_XOR_ASSIGN {$$ = $1;}
                        ;

TypeSpecifier:          // e.g. int
                        T_INT {$$ = $1;}
                        ;

%%


const Node *g_root; // Definition of variable (to match declaration earlier)

const Node *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
