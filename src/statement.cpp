#include "../include/statement.hpp"

// *********** BASIC STATEMENT CLASS ************ //

Statement::Statement(){};

// ************ COMPOUND STATEMENT CLASS ************ //

CompoundStatement::CompoundStatement(BlockItemPtr blockList) : blockList_(blockList) {

}

void CompoundStatement::print(){
    if(nextBlock_!=nullptr){
        nextBlock_->print();
    }
    if(blockList_!=nullptr){
        blockList_->print();
    }
}

Bindings CompoundStatement::printASM(Bindings bindings){
    Bindings initialBindings = bindings;
    if(nextBlock_!=nullptr){
        bindings = nextBlock_->printASM(bindings);
    }
    if(blockList_!=nullptr){
        blockList_->printASM(bindings);
    }
    return initialBindings;
}

void CompoundStatement::countVariables(int &count){
    if(nextBlock_!=nullptr){
        nextBlock_->countVariables(count);
    }
    if(blockList_!=nullptr){
        blockList_->countVariables(count);
    }
}

void CompoundStatement::countTemps(int &count){
    int tmpNextBlock = 0, tmpBlockList = 0;
    if(nextBlock_!=nullptr){
        nextBlock_->countTemps(tmpNextBlock);
    }
    if(blockList_!=nullptr){
        blockList_->countTemps(tmpBlockList);
    }
    count = std::max(tmpNextBlock,tmpBlockList);
}


// ************ EXPRESSION STATEMENT CLASS ************ //

ExpressionStatement::ExpressionStatement(ExpressionPtr expression) : expression_(expression) {

}

void ExpressionStatement::print(){
    if(nextBlock_!=nullptr){
        nextBlock_->print();
    }
    expression_->print();
}

Bindings ExpressionStatement::printASM(Bindings bindings){
    if(nextBlock_!=nullptr){
        bindings = nextBlock_->printASM(bindings);
    }
    if(expression_!=nullptr){
        expression_->printASM(bindings);
    }
    return bindings;
}

void ExpressionStatement::countVariables(int &count){
    if(nextBlock_!=nullptr){
        nextBlock_->countVariables(count);
    }
}

void ExpressionStatement::countTemps(int &count){
    int tmpNextBlock = 0, tmpExpression = 0;
    if(nextBlock_!=nullptr){
        nextBlock_->countTemps(tmpNextBlock);
    }
    expression_->countTemps(tmpExpression);
    count = std::max(tmpNextBlock,tmpExpression);
}


// *********** IF ELSE STATEMENT CLASS ************ //

IfElseStatement::IfElseStatement(ExpressionPtr condition, StatementPtr ifStatement, StatementPtr elseStatement) : condition_(condition), ifStatement_(ifStatement), elseStatement_(elseStatement) {

}

void IfElseStatement::print(){
    if(nextBlock_!=nullptr){
        nextBlock_->print();
    }
    std::cout << "if(";
    condition_->print();
    std::cout << "){" << std::endl;
    ifStatement_->print();
    std::cout << "}";
    if(elseStatement_!=nullptr){
        std::cout << "else{" << std::endl;
        elseStatement_->print();
        std::cout << "}";
    }
    std::cout << std::endl;
}

Bindings IfElseStatement::printASM(Bindings bindings){
    if(nextBlock_!=nullptr){
        bindings = nextBlock_->printASM(bindings);
    }

    int ifLabel = labelCount++;

    //print assembly for the condition
    condition_->printASM(bindings);
    output << "beq $2,$0,$" << ifLabel << "else" << std::endl;
    output << "nop" << std::endl;

    //print assembly for if statement
    ifStatement_->printASM(bindings);

    output << "b $" << ifLabel << "ifend" << std::endl;
    output << "nop" << std::endl << "$" << ifLabel << "else:" << std::endl;

    //print assembly for else statement
    if(elseStatement_!=nullptr){
        elseStatement_->printASM(bindings);
    }

    output << "$" << ifLabel << "ifend:" << std::endl;

    return bindings;
}

void IfElseStatement::countVariables(int &count){
    if(nextBlock_!=nullptr){
        nextBlock_->countVariables(count);
    }
    if(ifStatement_!=nullptr){
        ifStatement_->countVariables(count);
    }
    if(elseStatement_!=nullptr){
        elseStatement_->countVariables(count);
    }
}

void IfElseStatement::countTemps(int &count){
    int tmpNextBlock = 0, tmpCondition = 0, tmpIf = 0, tmpElse = 0;
    if(nextBlock_!=nullptr){
        nextBlock_->countTemps(tmpNextBlock);
    }
    if(condition_!=nullptr){
        condition_->countTemps(tmpCondition);
    }
    if(ifStatement_!=nullptr){
        ifStatement_->countTemps(tmpIf);
    }
    if(elseStatement_!=nullptr){
        elseStatement_->countTemps(tmpElse);
    }

    count = std::max(tmpNextBlock,std::max(tmpCondition,std::max(tmpIf,tmpElse)));

}


// *********** ITERATION STATEMENT CLASS ************ //

IterationStatement::IterationStatement(ExpressionPtr condition, StatementPtr statement) : condition_(condition), statement_(statement) {

}


// *********** WHILE LOOP CLASS ************ //

WhileLoop::WhileLoop(ExpressionPtr condition, StatementPtr statement, bool isDo) : IterationStatement(condition, statement), isDo_(isDo) {

}

void WhileLoop::print(){
    if(nextBlock_!=nullptr){
        nextBlock_->print();
    }
    std::cout << "while(";
    condition_->print();
    std::cout << "){";
    statement_->print();
    std::cout << "}" << std::endl;
}

Bindings WhileLoop::printASM(Bindings bindings){
    if(nextBlock_!=nullptr){
        bindings = nextBlock_->printASM(bindings);
    }

    int whileLabel = labelCount++;

    //output assembly

    if(!isDo_){
        output << "b $" << whileLabel << "whilecond" << std:: endl;
        output << "nop" << std::endl;
    }
    
    output << "$" << whileLabel << "whilebody:" << std::endl; 
    statement_->printASM(bindings);

    output << "$" << whileLabel << "whilecond:" << std::endl;
    condition_->printASM(bindings);

    output << "bne $2,$0,$" << whileLabel << "whilebody" << std::endl;
    output << "nop" << std::endl;

    return bindings;
}

void WhileLoop::countVariables(int &count){
    if(nextBlock_!=nullptr){
        nextBlock_->countVariables(count);
    }
    if(statement_!=nullptr){
        statement_->countVariables(count);
    }    
}

void WhileLoop::countTemps(int &count){
    int tmpNextBlock = 0, tmpCondition = 0, tmpStatement = 0;
    if(nextBlock_!=nullptr){
        nextBlock_->countTemps(tmpNextBlock);
    }
    if(condition_!=nullptr){
        condition_->countTemps(tmpCondition);
    }
    if(statement_!=nullptr){
        statement_->countTemps(tmpStatement);
    }

    count = std::max(tmpNextBlock,std::max(tmpCondition, tmpStatement));

}


// ***********DECLARATION FOR LOOP CLASS ************ //

DeclarationForLoop::DeclarationForLoop(DeclarationPtr initializer, ExpressionPtr condition, ExpressionPtr incrementer, StatementPtr statement) : IterationStatement(condition, statement), initializer_(initializer), incrementer_(incrementer) {

}

void DeclarationForLoop::print(){
    std::cout << "for loop" << std::endl;
}

Bindings DeclarationForLoop::printASM(Bindings bindings){
    if(nextBlock_!=nullptr){
        bindings = nextBlock_->printASM(bindings);
    }

    Bindings initialBindings = bindings;

    int forLabel = labelCount++;

    bindings = initializer_->printASM(bindings);
    output << "b $" << forLabel << "forcond" << std::endl;
    output << "nop" << std::endl;
    output << "$" << forLabel << "forbody:" << std::endl;
    statement_->printASM(bindings);
    incrementer_ ->printASM(bindings);
    output << "$" << forLabel << "forcond:" << std::endl;
    condition_->printASM(bindings);
    output << "bne $2,$0,$" << forLabel << "forbody" << std::endl;
    output << "nop" << std::endl;

    return initialBindings;
}

void DeclarationForLoop::countVariables(int &count){
    if(nextBlock_!=nullptr){
        nextBlock_->countVariables(count);
    }
    if(statement_!=nullptr){
        statement_->countVariables(count);
    }
    if(initializer_!=nullptr){
        count++;
    }
}

void DeclarationForLoop::countTemps(int &count){
int tmpNextBlock = 0, tmpCondition = 0, tmpStatement = 0, tmpInitializer = 0, tmpIncrementer = 0;
    if(nextBlock_!=nullptr){
        nextBlock_->countTemps(tmpNextBlock);
    }
    if(initializer_!=nullptr){
        initializer_->countTemps(tmpInitializer);
    }
    if(condition_!=nullptr){
        condition_->countTemps(tmpCondition);
    }
    if(incrementer_!=nullptr){
        incrementer_->countTemps(tmpIncrementer);
    }
    if(statement_!=nullptr){
        statement_->countTemps(tmpStatement);
    }

    count = std::max(tmpNextBlock,std::max(tmpCondition, std::max(tmpStatement, std::max(tmpInitializer, tmpIncrementer))));
}


// ***********EXPRESSION FOR LOOP CLASS ************ //

ExpressionForLoop::ExpressionForLoop(ExpressionPtr initializer, ExpressionPtr condition, ExpressionPtr incrementer, StatementPtr statement) : IterationStatement(condition, statement), initializer_(initializer), incrementer_(incrementer) {

}

void ExpressionForLoop::print(){
    std::cout << "for loop" << std::endl;
}

Bindings ExpressionForLoop::printASM(Bindings bindings){
    if(nextBlock_!=nullptr){
        bindings = nextBlock_->printASM(bindings);
    }

    Bindings initialBindings = bindings;

    int forLabel = labelCount++;

    initializer_->printASM(bindings);
    output << "b $" << forLabel << "forcond" << std::endl;
    output << "nop" << std::endl;
    output << "$" << forLabel << "forbody:" << std::endl;
    statement_->printASM(bindings);
    incrementer_ ->printASM(bindings);
    output << "$" << forLabel << "forcond:" << std::endl;
    condition_->printASM(bindings);
    output << "bne $2,$0,$" << forLabel << "forbody" << std::endl;
    output << "nop" << std::endl;

    return initialBindings;
}

void ExpressionForLoop::countVariables(int &count){
    if(nextBlock_!=nullptr){
        nextBlock_->countVariables(count);
    }
    if(statement_!=nullptr){
        statement_->countVariables(count);
    }
}

void ExpressionForLoop::countTemps(int &count){
int tmpNextBlock = 0, tmpCondition = 0, tmpStatement = 0, tmpInitializer = 0, tmpIncrementer = 0;
    if(nextBlock_!=nullptr){
        nextBlock_->countTemps(tmpNextBlock);
    }
    if(initializer_!=nullptr){
        initializer_->countTemps(tmpInitializer);
    }
    if(condition_!=nullptr){
        condition_->countTemps(tmpCondition);
    }
    if(incrementer_!=nullptr){
        incrementer_->countTemps(tmpIncrementer);
    }
    if(statement_!=nullptr){
        statement_->countTemps(tmpStatement);
    }

    count = std::max(tmpNextBlock,std::max(tmpCondition, std::max(tmpStatement, std::max(tmpInitializer, tmpIncrementer))));
}

// *********** JUMP STATEMENT CLASS ************ //


// *********** RETURN STATEMENT CLASS ************ //

ReturnStatement::ReturnStatement(ExpressionPtr expression) : expression_(expression){
    //TODO
}

void ReturnStatement::print(){
    if(nextBlock_!=nullptr){
        nextBlock_->print();
    }
    std::cout << "return";
    if(expression_!=nullptr){
        std::cout << " ";
        expression_->print();
        std::cout << std::endl;
    }
}

Bindings ReturnStatement::printASM(Bindings bindings){
    if(nextBlock_!=nullptr){
        bindings = nextBlock_->printASM(bindings);
    }
    if(expression_!=nullptr){
        expression_->printASM(bindings);
    }
    output << "j end" << std::endl << "nop" << std::endl;
    return bindings;
}

void ReturnStatement::countVariables(int &count){
    if(nextBlock_!=nullptr){
        nextBlock_->countVariables(count);
    }    
}

void ReturnStatement::countTemps(int &count){
    int tmpNextBlock = 0, tmpExpression = 0;
    if(nextBlock_!=nullptr){
        nextBlock_->countTemps(tmpNextBlock);
    }
    if(expression_!=nullptr){
        expression_->countTemps(tmpExpression);
    }

    count = std::max(tmpNextBlock,tmpExpression);
}