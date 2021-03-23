#include "../include/bindings.hpp"

Bindings::Bindings() : stackPos_(0), tempStackPos_(0) {

}

void Bindings::insertBindings(std::string id, std::string type, int stackPosition){
    int pos;
    if(stackPosition==-1){
        pos = getStackPos();
    } else {
        pos = stackPosition;
    }

    VariableData tmp = {type, pos};
    bindings_[id] = tmp;
}

int Bindings::getStackPos(){
    return stackPos_;
}

int Bindings::getStackPos(std::string id){
    if(bindings_.find(id)!=bindings_.end()){
        return bindings_[id].stackPosition;
    } else {
        return -1;
    }
}   

void Bindings::increaseStackPos(int n){
    stackPos_ += n;
}

void Bindings::increaseStackPos(){
    stackPos_ += 4;
}

void Bindings::setStackPos(int n){
    stackPos_ = n;
}

void Bindings::nextTempPos(){
    tempStackPos_ += 4;
}

int Bindings::getTempPos(){
    return tempStackPos_;
}

void Bindings::setTempPos(int n){
    tempStackPos_ = n;
}

void Bindings::setFunctionEndLabel(int n){
    functionEndLabel_ = n;
}

int Bindings::getFunctionEndLabel(){
    return functionEndLabel_;
}
