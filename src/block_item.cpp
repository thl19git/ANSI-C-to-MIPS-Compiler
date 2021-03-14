#include "../include/block_item.hpp"

BlockItem::BlockItem(){

}
void BlockItem::linkBlock(BlockItemPtr nextBlock){
    nextBlock_ = nextBlock;
}

BlockItemPtr BlockItem::getNext(){
    return nextBlock_;
}