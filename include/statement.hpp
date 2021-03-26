#ifndef statement_hpp
#define statement_hpp

#include "node.hpp"
#include "statement.hpp"
#include "declaration.hpp"
#include "expression.hpp"
#include "block_item.hpp"
#include <vector>
#include <iostream>
#include "bindings.hpp"

class Statement;
typedef Statement* StatementPtr;

// *********** BASIC STATEMENT CLASS ************ //

class Statement : public BlockItem{
protected:

public:
    Statement();
    virtual void print() = 0;
    virtual Bindings printASM(Bindings bindings) = 0;
    virtual void countVariables(int &count) = 0;
    virtual void countTemps(int &count) = 0;
    virtual void countArgs(int &count) = 0;
};


// ************ COMPOUND STATEMENT CLASS ************ //

class CompoundStatement : public Statement{
protected:
    BlockItemPtr blockList_;

public:
    CompoundStatement(BlockItemPtr blockList);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countVariables(int &count);
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);

};


// ************ EXPRESSION STATEMENT CLASS ************ //

class ExpressionStatement : public Statement{
protected:
    ExpressionPtr expression_;

public:
    ExpressionStatement(ExpressionPtr expression = nullptr);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countVariables(int &count);
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);

};


// *********** IF ELSE STATEMENT CLASS ************ //

class IfElseStatement : public Statement{
protected:
    ExpressionPtr condition_;
    StatementPtr ifStatement_;
    StatementPtr elseStatement_;

public:
    IfElseStatement(ExpressionPtr condition, StatementPtr ifStatement, StatementPtr elseStatement = nullptr);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countVariables(int &count);
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);
};


// *********** ITERATION STATEMENT CLASS ************ //

class IterationStatement : public Statement{
protected:
    ExpressionPtr condition_;
    StatementPtr statement_;

public:
    IterationStatement(ExpressionPtr condition, StatementPtr statement);
    virtual void print() = 0;
    virtual Bindings printASM(Bindings bindings) = 0;
    virtual void countVariables(int &count) = 0;
    virtual void countTemps(int &count) = 0;
    virtual void countArgs(int &count) = 0;
};


// *********** WHILE LOOP CLASS ************ //

class WhileLoop : public IterationStatement{
protected:
    bool isDo_;
public:
    WhileLoop(ExpressionPtr condition, StatementPtr statement, bool isDo = false);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countVariables(int &count);
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);
};


// *********** DECLARATION FOR LOOP CLASS ************ //

class DeclarationForLoop : public IterationStatement{
protected:
    DeclarationPtr initializer_;
    ExpressionPtr incrementer_;

public:
    DeclarationForLoop(DeclarationPtr initializer, ExpressionPtr condition, ExpressionPtr incrementer, StatementPtr statement);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countVariables(int &count);
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);
};


// *********** EXPRESSION FOR LOOP CLASS ************ //

class ExpressionForLoop : public IterationStatement{
protected:
    ExpressionPtr initializer_;
    ExpressionPtr incrementer_;

public:
    ExpressionForLoop(ExpressionPtr initializer, ExpressionPtr condition, ExpressionPtr incrementer, StatementPtr statement);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countVariables(int &count);
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);
};



// *********** JUMP STATEMENT CLASS ************ //

class JumpStatement : public Statement{
protected:

public:
    virtual void print() = 0;
    virtual Bindings printASM(Bindings bindings) = 0;
    virtual void countVariables(int &count) = 0;
    virtual void countTemps(int &count) = 0;
    virtual void countArgs(int &count) = 0;
};


// *********** RETURN STATEMENT CLASS ************ //

class ReturnStatement : public JumpStatement{
protected:
    ExpressionPtr expression_;

public:
    ReturnStatement(ExpressionPtr expression = nullptr);
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countVariables(int &count);
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);
};


// *********** BREAK STATEMENT CLASS ************ //

class BreakStatement : public JumpStatement{
protected:

public:
    BreakStatement();
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countVariables(int &count);
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);
};


// *********** CONTINUE STATEMENT CLASS ************ //

class ContinueStatement : public JumpStatement{
protected:

public:
    ContinueStatement();
    virtual void print();
    virtual Bindings printASM(Bindings bindings);
    virtual void countVariables(int &count);
    virtual void countTemps(int &count);
    virtual void countArgs(int &count);
};
#endif
