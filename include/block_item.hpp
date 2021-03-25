#ifndef block_item_hpp
#define block_item_hpp

#include "node.hpp"
#include "bindings.hpp"

class BlockItem;

typedef BlockItem* BlockItemPtr;

class BlockItem : public Node {
protected:
    BlockItemPtr nextBlock_;
public:
    BlockItem();
    virtual void print()=0;
    virtual Bindings printASM(Bindings bindings)=0;
    virtual void countVariables(int &count) = 0;
    virtual void countTemps(int &count) = 0;
    virtual void countArgs(int &count) = 0; 
    void linkBlock(BlockItemPtr nextBlock);
    BlockItemPtr getNext();
};


#endif