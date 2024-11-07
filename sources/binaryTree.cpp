#include <stdlib.h>
#include <stdint.h>

#include "binaryTree.h"


//--------------------------------------------------------------------------------------------------


struct BinTreeNode
{
    BinTreeNode* leftNode;
    BinTreeNode* rightNode;
    uint8_t      value[];
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


static BinTreeNode* BinTreeNodeCreate(BinTree* binTree);


//--------------------------------------------------------------------------------------------------


bool BinTreeInit(BinTree** binTree, const size_t valueSize, comparator_t* Compare
                                                _BIN_TREE_ON_DEBUG(, VariableInitInfo initInfo))
{
    if (binTree == NULL || *binTree != NULL)
        return false;

    *binTree = (BinTree*) calloc(1, sizeof(BinTree));
    if (*binTree == NULL)
        return false;
    
    (*binTree)->Compare   = Compare;
    (*binTree)->valueSize = valueSize;

    return true;
}


void BinTreeDelete(BinTree** binTree)
{

}


//--------------------------------------------------------------------------------------------------


static BinTreeNode* BinTreeNodeCreate(BinTree* binTree)
{
    
}
