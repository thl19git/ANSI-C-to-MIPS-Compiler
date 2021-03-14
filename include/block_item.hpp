#ifndef block_item_hpp
#define block_item_hpp

#include "node.hpp"

class BlockItem;

typedef BlockItem* BlockItemPtr;

class BlockItem : public Node {
protected:
    NodePtr block_;
    BlockItemPtr nextBlock_;
public:
    BlockItem(NodePtr block = nullptr);
    void print();
    void printASM(/*Bindings* bindings*/);
    void linkBlock(BlockItemPtr nextBlock);
    BlockItemPtr getNext();
};


#endif