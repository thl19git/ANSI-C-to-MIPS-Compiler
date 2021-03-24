#include "../include/parameter.hpp"

Parameter::Parameter(std::string type, std::string id) : type_(type), id_(id) {

}

void Parameter::linkParameter(ParameterPtr parameter){
    nextParameter_ = parameter;
}

Bindings Parameter::printParameterASM(Bindings bindings, int mem, int num){
    if(nextParameter_!=nullptr){
        bindings = nextParameter_->printParameterASM(bindings, mem-4, num-1);
    }

    if(num >= 1 && num <= 4){
        output << "sw $" << num+3 << "," << mem << "($fp)" << std::endl;
    }

    bindings.insertBindings(id_, type_, mem);

    return bindings;
}

int Parameter::countParameters(){
    if(nextParameter_!=nullptr){
        return 1 + nextParameter_->countParameters();
    } else {
        return 1;
    }
}

void Parameter::print(){

}

Bindings Parameter::printASM(Bindings bindings){
    return bindings;
}