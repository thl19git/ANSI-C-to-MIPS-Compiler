#include "../include/declaration.hpp"

// *********** BASIC DECLARATION CLASS ************ //

Declaration::Declaration(){
    //Do nothing
}

void Declaration::linkDeclaration(DeclarationPtr declaration){
    nextDeclaration_ = declaration;
}

void Declaration::setType(std::string type){
    type_ = type;
}

DeclarationPtr Declaration::getNext(){
    return nextDeclaration_;
}

void Declaration::setInitializer(ExpressionPtr initializer){
    //do nothing
}


// *********** IDENTIFIER DECLARATION CLASS ************ //

IdentifierDeclaration::IdentifierDeclaration(std::string id, ExpressionPtr initializer) : id_(id), initializer_(initializer){

}

void IdentifierDeclaration::print(){
    if(nextBlock_!=nullptr){
        nextBlock_->print();
    }
    if(nextDeclaration_!=nullptr){
        nextDeclaration_->print();
    }
    std::cout <<" " << type_ << " " << id_ << " ";
    if(initializer_!=nullptr){
        std::cout << "=";
        initializer_->print();
    }
}

Bindings IdentifierDeclaration::printASM(Bindings bindings){
    if(nextBlock_!=nullptr){
        bindings = nextBlock_->printASM(bindings);
    }

    //puts the initializer in the stack and $2
    if(initializer_!=nullptr){
        initializer_->printASM(bindings);
        bindings.insertBindings(id_, type_);
        output << "sw $2," << bindings.getStackPos() << "($fp)" << std::endl;
        bindings.increaseStackPos();
    } else {
        bindings.insertBindings(id_, type_);
        bindings.increaseStackPos();
    }



    return bindings;
}

std::string IdentifierDeclaration::getId(){
    return id_;
}

void IdentifierDeclaration::countVariables(int &count){
    if(nextBlock_!=nullptr){
        nextBlock_->countVariables(count);
    }
    count++;
}

void IdentifierDeclaration::countTemps(int &count){
    int tmpNextBlock = 0, tmpInit = 0;
    if(nextBlock_!=nullptr){
        nextBlock_->countTemps(tmpNextBlock);
    }
    if(initializer_!=nullptr){
        initializer_->countTemps(tmpInit);
    }

    count = std::max(tmpNextBlock,tmpInit);
}

void IdentifierDeclaration::countArgs(int &count){
    int tmpNextBlock = 0, tmpInit = 0;
    if(nextBlock_!=nullptr){
        nextBlock_->countArgs(tmpNextBlock);
    }
    if(initializer_!=nullptr){
        initializer_->countArgs(tmpInit);
    }

    count = std::max(tmpNextBlock,tmpInit);
}

void IdentifierDeclaration::setInitializer(ExpressionPtr initializer){
    initializer_ = initializer;
}


// *********** ARRAY DECLARATION CLASS ************ //

ArrayDeclaration::ArrayDeclaration(std::string id, int size) : id_(id), size_(size){

}

void ArrayDeclaration::print(){
    if(nextBlock_!=nullptr){
        nextBlock_->print();
    }
    if(nextDeclaration_!=nullptr){
        nextDeclaration_->print();
    }
    std::cout << "array declaration" << std::endl;
}

Bindings ArrayDeclaration::printASM(Bindings bindings){
    if(nextBlock_!=nullptr){
        bindings = nextBlock_->printASM(bindings);
    }

    //insert array name at index 0 in bindings
    bindings.insertBindings(id_, type_);
    bindings.increaseStackPos(4*size_);
    return bindings;
}

std::string ArrayDeclaration::getId(){
    return id_;
}

void ArrayDeclaration::countVariables(int &count){
    if(nextBlock_!=nullptr){
        nextBlock_->countVariables(count);
    }
    count+= size_;
}

void ArrayDeclaration::countTemps(int &count){
    if(nextBlock_!=nullptr){
        nextBlock_->countTemps(count);
    }
}

void ArrayDeclaration::countArgs(int &count){
    if(nextBlock_!=nullptr){
        nextBlock_->countArgs(count);
    }
}