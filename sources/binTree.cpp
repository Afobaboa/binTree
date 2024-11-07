#include <stdlib.h>
#include <stdint.h>

#include "binTree.h"
#include "binTreeStructs.h"


//--------------------------------------------------------------------------------------------------


static BinTreeNode* BinTreeNodeCreate(BinTree* binTree);
static void BinTreeNodeDelete(BinTreeNode* node);


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

    (*binTree)->root = BinTreeNodeCreate(*binTree);
    if ((*binTree)->root == NULL)
        return false;

    return true;
}


void BinTreeDelete(BinTree** binTree)
{
    if (binTree == NULL || *binTree == NULL)
        return;

    BinTreeNodeDelete((*binTree)->root);

    (*binTree)->root      = NULL;
    (*binTree)->Compare   = NULL;
    (*binTree)->valueSize = 0;

    *binTree = NULL;
}


//--------------------------------------------------------------------------------------------------


static BinTreeNode* BinTreeNodeCreate(BinTree* binTree)
{
    return (BinTreeNode*) calloc(1, BIN_TREE_NODE_SIZE(binTree));
}


static void BinTreeNodeDelete(BinTreeNode* node)
{
    if (node->leftNode != NULL)
        BinTreeNodeDelete(node->leftNode);
    
    if (node->rightNode != NULL)
        BinTreeNodeDelete(node->rightNode);

    free(node);
}
