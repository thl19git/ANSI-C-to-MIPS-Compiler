/*So far covers all expressions / structures in the basic feature set bar variable 
  declaration and initialisation. Precedence and associativity is encoded in the
  grammar. */

%code requires{
    #include //stuff to include

    extern const /*root node type*/ *g_root; // A way of getting the AST out

    int yylex(void)
    void yyerror(const char *)
}

%token T_IDENTIFIER T_INT_CONST
%token T_INT
%token T_IF T_ELSE T_WHILE T_RETURN
%token T_PLUS T_ADD_ASSIGN T_MINUS T_SUB_ASSIGN T_MULT T_MULT_ASSIGN T_DIV T_DIV_ASSIGN 
%token T_MOD T_MOD_ASSIGN T_AND T_AND_ASSIGN T_OR T_OR_ASSIGN T_XOR T_XOR_ASSIGN T_EQUAL
%token T_RSHIFT_OP T_RSHIFT_ASSIGN T_LSHIFT_OP T_LSHIFT_ASSIGN T_INC_OP T_DEC_OP T_AND_OP T_OR_OP T_LTE_OP T_GTE_OP
%token T_LT T_GT T_QUESTION T_NOT T_INVERT T_DOT T_EQUAL_OP T_NEQUAL_OP
%token T_SEMICOLON T_COMMA T_COLON
%token T_LB T_RB T_LCB T_RCB T_LSB T_RSB

%union //define some type related stuff here

%type //define types here

%start ROOT

%%

ROOT: TranslationUnit {;}
      ;

TranslationUnit:        FunctionDefinition {;}
                        ;
                
FunctionDefinition:     TypeSpecifier T_IDENTIFIER T_LB T_RB CompoundStatement {;}
                        ;

CompoundStatement:      T_LCB T_RCB {;}
                        | T_LCB StatementList T_RCB {;}
                        ;

StatementList:          Statement {;}
                        | StatementList Statement {;}
                        ;

Statement:              ExpressionStatement {;}
                        | SelectionStatement {;}
                        | IterationStatment {;}
                        | JumpStatement {;}
                        | CompoundStatement {;}
                        ;

ExpressionStatement:    T_SEMICOLON {;}
                        | Expression T_SEMICOLON {;}
                        ;

SelectionStatement:     T_IF T_LB Expression T_RB Statement {;}
                        | T_IF T_LB Expression T_RB Statement T_ELSE Statement {;}
                        ;

IterationStatment:      T_WHILE T_LB Expression T_RB Statement {;}
                        ;

JumpStatement:          T_RETURN T_SEMICOLON {;}
                        | T_RETURN Expression T_SEMICOLON {;}
                        ;

Expression:             AssignmentExpression {;}
                        | Expression T_COMMA AssignmentExpression {;}
                        ;

AssignmentExpression:   ConditionalExpression {;}
                        | UnaryExpression AssignmentOperator AssignmentExpression {;}
                        ;

ConditionalExpression:  LogicalOrExpression {;}
                        | LogicalOrExpression T_QUESTION  Expression T_COLON ConditionalExpression {;}
                        ;

LogicalOrExpression:    LogicalAndExpression {;}
                        | LogicalOrExpression T_OR_OP LogicalAndExpression {;}
                        ;

LogicalAndExpression:   InclusiveOrExpression {;}
                        | LogicalAndExpression T_AND_OP InclusiveOrExpression {;}
                        ;

InclusiveOrExpression:  ExclusiveOrExpression {;}
                        | InclusiveOrExpression T_OR ExclusiveOrExpression {;}
                        ;

ExclusiveOrExpression:  AndExpression {;}
                        | ExclusiveOrExpression T_XOR AndExpression {;}
                        ;

AndExpression:          EqualityExpression {;}
                        | AndExpression T_AND EqualityExpression {;}
                        ;

EqualityExpression:     RelationalExpression {;}
                        | EqualityExpression T_EQUAL_OP RelationalExpression {;}
                        | EqualityExpression T_NEQUAL_OP RelationalExpression {;}
                        ;

RelationalExpression:   ShiftExpression {;}
                        | RelationalExpression T_LT ShiftExpression {;}
                        | RelationalExpression T_GT ShiftExpression {;}
                        | RelationalExpression T_LTE_OP ShiftExpression {;}
                        | RelationalExpression T_GTE_OP ShiftExpression {;}
                        ;

ShiftExpression:        AdditiveExpression {;}
                        | ShiftExpression T_LSHIFT_OP AdditiveExpression {;}
                        | ShiftExpression T_RSHIFT_OP AdditiveExpression {;}
                        ;

AdditiveExpression:     MultiplicativeExpression {;}
                        | AdditiveExpression T_PLUS MultiplicativeExpression {;}
                        | AdditiveExpression T_MINUS MultiplicativeExpression {;}
                        ;

MultiplicativeExpression:
                        UnaryExpression {;}
                        | MultiplicativeExpression T_MULT UnaryExpression {;}
                        | MultiplicativeExpression T_DIV UnaryExpression {;}
                        | MultiplicativeExpression T_MOD UnaryExpression {;}
                        ;

UnaryExpression:        PostfixExpression {;}
                        | UnaryOperator UnaryExpression {;}
                        ;

UnaryOperator:          T_INC_OP {;}
                        | T_DEC_OP {;}
                        | T_PLUS {;}
                        | T_MINUS {;}
                        | T_NOT {;}
                        | T_INVERT {;}
                        ;

PrimaryExpression:      T_IDENTIFIER {;}
                        | T_INT_CONST {;}
                        | T_LB Expression T_RB {;}
                        ;
                        

PostfixExpression:      PrimaryExpression {;}
                        | PostfixExpression T_INC_OP {;}
                        | PostfixExpression T_DEC_OP {;}
                        ;

AssignmentOperator:     T_EQUAL {;}
                        | T_ADD_ASSIGN {;}
                        | T_SUB_ASSIGN {;}
                        | T_MULT_ASSIGN {;}
                        | T_DIV_ASSIGN {;}
                        | T_MOD_ASSIGN {;}
                        | T_LSHIFT_ASSIGN {;}
                        | T_RSHIFT_ASSIGN {;}
                        | T_AND_ASSIGN {;}
                        | T_OR_ASSIGN {;}
                        | T_XOR_ASSIGN {;}
                        ;

TypeSpecifier:          T_INT {;}
                        ;

%%

const /*root node type*/ *g_root; //Definition of variable (to match declaration earlier)

const /*root node type*/ *parseAST(){
    g_root = 0;
    yyparse();
    return g_root;
}