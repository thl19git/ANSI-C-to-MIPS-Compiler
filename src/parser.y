/*So far covers all expressions / structures in the basic feature set. Precedence and associativity is encoded in the
  grammar. */

%code requires{
  int yylex(void);
  void yyerror(const char *);
  #include <string>
  #include "../include/ast.hpp"
  //extern const Expression *g_root; // A way of getting the AST out
}

%union{
  std::string *string;
  double number
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

%type <string> T_IDENTIFIER AssignmentOperator UnaryOperator

%type <number> T_INT_CONST

%type <node> ROOT

%type <transunit> TranslationUnit

%type <function> FunctionDefinition

%type <statement> Statement StatementList IterationStatment JumpStatement ExpressionStatement SelectionStatement CompoundStatement

%type <expression> Expression PrimaryExpression PostfixExpression ConditionalExpression UnaryExpression Initializer InitDeclaratorList
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
                        TypeSpecifier Declarator CompoundStatement {;}
                        | Declarator CompoundStatement {;}
                        ;

CompoundStatement:      // e.g. {int x = 5; return x + 3;}
                        T_LCB T_RCB {;}
                        | T_LCB StatementList T_RCB {;}
                        | T_LCB DeclarationList T_RCB {;}
                        | T_LCB DeclarationList StatementList T_RCB {;}
                        ;

DeclarationList:        // e.g. int x; int y = 5;
                        Declaration {;}
                        | DeclarationList Declaration {;}
                        ;

Declaration:            // e.g int x; || int x = 5;
                        TypeSpecifier InitDeclaratorList T_SEMICOLON {;}
                        ;


InitDeclaratorList:     // e.g. x; || x , y || int a = 1, b = 2
                        InitDeclarator {;}
                        | InitDeclaratorList T_COMMA InitDeclarator {;}
                        ;

InitDeclarator:         // e.g. a || a = 1
                        Declarator {;}
                        | Declarator T_EQUAL Initializer {;}
                        ;

Declarator:             // e.g. a || sum
                        DirectDeclarator {;}
                        ;

DirectDeclarator:       // e.g. a || sum
                        T_IDENTIFIER {;}
                        | T_LB Declarator T_RB {;}
                        | DirectDeclarator T_LB T_RB {;}
                        ;

Initializer:            // e.g. a || b = 2
                        AssignmentExpression {;}
                        | T_LCB InitializerList T_RCB {;}
                        | T_LCB InitializerList T_COMMA T_RCB {;}
                        ;

InitializerList:        // e.g. a || a,b
                        Initializer {;}
                        | InitializerList T_COMMA Initializer {;}
                        ;

StatementList:          // e.g. a = 5; return a;
                        Statement {;}
                        | StatementList Statement {;}
                        ;

Statement:              // e.g. a = 5; || return 7; || {int x = 5; return x + 3;}
                        ExpressionStatement {;}
                        | SelectionStatement {;}
                        | IterationStatment {;}
                        | JumpStatement {;}
                        | CompoundStatement {;}
                        ;

ExpressionStatement:    // e.g. a = 5; || a,b,c; || x;
                        T_SEMICOLON {;}
                        | Expression T_SEMICOLON {;}
                        ;

SelectionStatement:     // e.g. if(a){...} || if(x+3) {...} else {...}
                        T_IF T_LB Expression T_RB Statement {;}
                        | T_IF T_LB Expression T_RB Statement T_ELSE Statement {;}
                        ;

IterationStatment:      // e.g. while (x > 3) {...}
                        T_WHILE T_LB Expression T_RB Statement {;}
                        ;

JumpStatement:          // e.g. return; || return x == y;
                        T_RETURN T_SEMICOLON {;}
                        | T_RETURN Expression T_SEMICOLON {;}
                        ;

Expression:             // e.g. a = 5 || a,b,c || x
                        AssignmentExpression {;}
                        | Expression T_COMMA AssignmentExpression {;}
                        ;

AssignmentExpression:   // e.g. a = 5 || a += 2
                        ConditionalExpression {;}
                        | UnaryExpression AssignmentOperator AssignmentExpression {;}
                        ;

ConditionalExpression:  // e.g. x == y ? a = 1 : b = 3
                        LogicalOrExpression {;}
                        | LogicalOrExpression T_QUESTION  Expression T_COLON ConditionalExpression {;}
                        ;

LogicalOrExpression:    // e.g. x || y
                        LogicalAndExpression {;}
                        | LogicalOrExpression T_OR_OP LogicalAndExpression {;}
                        ;

LogicalAndExpression:   // e.g. x && y
                        InclusiveOrExpression {;}
                        | LogicalAndExpression T_AND_OP InclusiveOrExpression {;}
                        ;

InclusiveOrExpression:  // e.g. x | y
                        ExclusiveOrExpression {;}
                        | InclusiveOrExpression T_OR ExclusiveOrExpression {;}
                        ;

ExclusiveOrExpression:  // e.g. x ^ y
                        AndExpression {;}
                        | ExclusiveOrExpression T_XOR AndExpression {;}
                        ;

AndExpression:          // e.g. x & y
                        EqualityExpression {;}
                        | AndExpression T_AND EqualityExpression {;}
                        ;

EqualityExpression:     // e.g. x == y || x != y
                        RelationalExpression {;}
                        | EqualityExpression T_EQUAL_OP RelationalExpression {;}
                        | EqualityExpression T_NEQUAL_OP RelationalExpression {;}
                        ;

RelationalExpression:   // e.g. x > y || x <= y
                        ShiftExpression {;}
                        | RelationalExpression T_LT ShiftExpression {;}
                        | RelationalExpression T_GT ShiftExpression {;}
                        | RelationalExpression T_LTE_OP ShiftExpression {;}
                        | RelationalExpression T_GTE_OP ShiftExpression {;}
                        ;

ShiftExpression:        // e.g. x << 2 || y >> 4
                        AdditiveExpression {;}
                        | ShiftExpression T_LSHIFT_OP AdditiveExpression {;}
                        | ShiftExpression T_RSHIFT_OP AdditiveExpression {;}
                        ;

AdditiveExpression:     // e.g. x + y || x - y
                        MultiplicativeExpression {;}
                        | AdditiveExpression T_PLUS MultiplicativeExpression {;}
                        | AdditiveExpression T_MINUS MultiplicativeExpression {;}
                        ;

MultiplicativeExpression:
                        // e.g. x * y || x / y || x % y
                        UnaryExpression {;}
                        | MultiplicativeExpression T_MULT UnaryExpression {;}
                        | MultiplicativeExpression T_DIV UnaryExpression {;}
                        | MultiplicativeExpression T_MOD UnaryExpression {;}
                        ;

UnaryExpression:        // e.g. !x || ++y
                        PostfixExpression {;}
                        | UnaryOperator UnaryExpression {;}
                        ;

UnaryOperator:          // e.g. ++ || ! || ~
                        T_INC_OP {$$ = "++";}
                        | T_DEC_OP {$$ = "--";}
                        | T_PLUS {$$ = "+";}
                        | T_MINUS {$$ = "-";}
                        | T_NOT {$$ = "!";}
                        | T_INVERT {$$ = "~";}
                        ;

PrimaryExpression:      // e.g. a || 4 || ()
                        T_IDENTIFIER {;}
                        | T_INT_CONST {;}
                        | T_LB Expression T_RB {;}
                        ;
                        

PostfixExpression:      // e.g. a++
                        PrimaryExpression {;}
                        | PostfixExpression T_INC_OP {;}
                        | PostfixExpression T_DEC_OP {;}
                        ;

AssignmentOperator:     // e.g +=
                        T_EQUAL {$$ = "=";}
                        | T_ADD_ASSIGN {$$ = "+=";}
                        | T_SUB_ASSIGN {$$ = "-=";}
                        | T_MULT_ASSIGN {$$ = "*=";}
                        | T_DIV_ASSIGN {$$ = "/=";}
                        | T_MOD_ASSIGN {$$ = "%=";}
                        | T_LSHIFT_ASSIGN {$$ = "<<=";}
                        | T_RSHIFT_ASSIGN {$$ = ">>=";}
                        | T_AND_ASSIGN {$$ = "&=";}
                        | T_OR_ASSIGN {$$ = "|=";}
                        | T_XOR_ASSIGN {$$ = "^=";}
                        ;

TypeSpecifier:          // e.g. int
                        T_INT {;}
                        ;

%%

/*to do: extract AST

const Expression *g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}

*/
void parseAST(){
  yyparse();
}