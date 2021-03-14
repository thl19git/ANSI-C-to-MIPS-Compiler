#include "../include/block_item.hpp"

BlockItem::BlockItem(NodePtr block) : block_(block) {

}

void BlockItem::print(){
    if(nextBlock_!=nullptr){
        nextBlock_->print();
    }
    block_->print();
}

void BlockItem::printASM(){

}

void BlockItem::linkBlock(BlockItemPtr nextBlock){
    nextBlock_ = nextBlock;
}

BlockItemPtr BlockItem::getNext(){
    return nextBlock_;
}