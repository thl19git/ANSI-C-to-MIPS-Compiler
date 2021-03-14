#ifndef block_item_hpp
#define block_item_hpp

#include "node.hpp"

class BlockItem;

typedef BlockItem* BlockItemPtr;

class BlockItem : public Node {
protected:
    BlockItemPtr nextBlock_;
public:
    BlockItem();
    virtual void print()=0;
    virtual void printASM(/*Bindings* bindings*/)=0;
    void linkBlock(BlockItemPtr nextBlock);
    BlockItemPtr getNext();
};


#endif