#ifndef BIN_TREE_STRUCTS_H
#define BIN_TREE_STRUCTS_H


//--------------------------------------------------------------------------------------------------

#include <stdint.h>

#include "binTree.h"


struct BinTreeNode
{
    BinTreeNode* leftNode;
    BinTreeNode* rightNode;
    uint8_t      valuePtr[];
};

#define BIN_TREE_NODE_SIZE(binTree) \
    sizeof(BinTreeNode) + binTree->valueSize


struct BinTree 
{
    BinTreeNode*  root;
    comparator_t* Compare;
    size_t        valueSize;
};


//--------------------------------------------------------------------------------------------------


#endif // BIN_TREE_STRUCTS_H