#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "binTree.h"
#include "binTreeStructs.h"


//--------------------------------------------------------------------------------------------------


static BinTreeNode* BinTreeNodeCreate(binTree_t binTree);
static void BinTreeNodeDelete(BinTreeNode* node);

static void BinTreeNodeSetValue(BinTreeNode* node, const void* valuePtr, const size_t valueSize);
static void BinTreeNodeInsert(BinTreeNode* root, BinTreeNode* node, comparator_t Compare);


//--------------------------------------------------------------------------------------------------


bool BinTreeInit(binTree_t* binTree, const size_t valueSize, comparator_t Compare
                                                _BIN_TREE_ON_DEBUG(, VariableInitInfo initInfo))
{
    if (binTree == NULL || *binTree != NULL)
        return false;

    *binTree = (BinTree*) calloc(1, sizeof(BinTree));
    if (*binTree == NULL)
        return false;

    #ifdef _BIN_TREE_DEBUG
    (*binTree)->initInfo = initInfo;
    #endif // _BIN_TREE_DEBUG
    
    (*binTree)->Compare   = Compare;
    (*binTree)->valueSize = valueSize;

    (*binTree)->root = BinTreeNodeCreate(*binTree);
    if ((*binTree)->root == NULL)
        return false;

    return true;
}


void BinTreeDelete(binTree_t* binTree)
{
    if (binTree == NULL || *binTree == NULL)
        return;

    BinTreeNodeDelete((*binTree)->root);

    (*binTree)->root      = NULL;
    (*binTree)->Compare   = NULL;
    (*binTree)->valueSize = 0;

    free(*binTree);
    *binTree = NULL;
}


bool BinTreeInsert(binTree_t binTree, void* valuePtr)
{
    #ifdef _BIN_TREE_DEBUG
    if (binTree == NULL || binTree->root == NULL || valuePtr == NULL)
        return false;
    #endif // _BIN_TREE_DEBUG

    BinTreeNode* nodeToInsert = BinTreeNodeCreate(binTree);
    if (nodeToInsert == NULL)
        return false;

    BinTreeNodeSetValue(nodeToInsert, valuePtr, binTree->valueSize);
    BinTreeNodeInsert(binTree->root, nodeToInsert, binTree->Compare);

    return true;
}


//--------------------------------------------------------------------------------------------------


static BinTreeNode* BinTreeNodeCreate(binTree_t binTree)
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


static void BinTreeNodeSetValue(BinTreeNode* node, const void* valuePtr, const size_t valueSize)
{
    memmove(node->valuePtr, valuePtr, valueSize);
}


static void BinTreeNodeInsert(BinTreeNode* root, BinTreeNode* node, comparator_t Compare)
{
    if (Compare(node->valuePtr, root->valuePtr) < 0)
    {
        if (root->leftNode != NULL)
            BinTreeNodeInsert(root->leftNode, node, Compare);
        else
            root->leftNode = node;
    }
    else
    {
        if (root->rightNode != NULL)
            BinTreeNodeInsert(root->rightNode, node, Compare);
        else
            root->rightNode = node;
    }
}
