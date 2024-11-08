#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "binTree.h"
#include "binTreeStructs.h"


//--------------------------------------------------------------------------------------------------


static bool BinTreeVerify(binTree_t binTree);
static bool ValuePtrVerify(void* valuePtr);

static BinTreeNode* BinTreeNodeCreate(binTree_t binTree);
static void BinTreeNodeDelete(BinTreeNode* node);

static void BinTreeNodeSetValue(BinTreeNode* node, const void* valuePtr, const size_t valueSize);
static void BinTreeNodeInsert(BinTreeNode* root, BinTreeNode* node, comparator_t Compare);
static void BinTreeNodeValueDelete(BinTreeNode** root, void* valuePtr, comparator_t Compare);


//--------------------------------------------------------------------------------------------------


bool BinTreeInit(binTree_t* binTree, const size_t valueSize, const void* rootValuePtr, 
                            comparator_t Compare _BIN_TREE_ON_DEBUG(, VariableInitInfo initInfo))
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
    
    BinTreeNodeSetValue((*binTree)->root, rootValuePtr, valueSize);

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
    if (!BinTreeVerify(binTree) || !ValuePtrVerify(valuePtr))
        return false;

    BinTreeNode* nodeToInsert = BinTreeNodeCreate(binTree);
    if (nodeToInsert == NULL)
        return false;

    BinTreeNodeSetValue(nodeToInsert, valuePtr, binTree->valueSize);
    BinTreeNodeInsert(binTree->root, nodeToInsert, binTree->Compare);

    return true;
}


bool BinTreeValueDelete(binTree_t binTree, void* valuePtr)
{
    if (!BinTreeVerify(binTree) || !ValuePtrVerify(valuePtr))
        return false;

    if (binTree->Compare(valuePtr, binTree->root->valuePtr) == 0)
        return false;

    BinTreeNodeValueDelete(&binTree->root, valuePtr, binTree->Compare);
    
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


static void BinTreeNodeValueDelete(BinTreeNode** root, void* valuePtr, comparator_t Compare)
{
    if (Compare(valuePtr, (*root)->valuePtr) < 0 && (*root)->leftNode != NULL)
        BinTreeNodeValueDelete(&(*root)->leftNode, valuePtr, Compare);

    else if (Compare(valuePtr, (*root)->valuePtr) > 0 && (*root)->rightNode != NULL)
        BinTreeNodeValueDelete(&(*root)->rightNode, valuePtr, Compare);
    
    else if (Compare(valuePtr, (*root)->valuePtr) == 0)
    {
        BinTreeNodeDelete(*root);
        *root = NULL;
    }
}


#ifndef _BIN_TREE_QUIET_VERIFY
    #define _QUIET(...) __VA_ARGS__
#else
    #define _QUIET(...)  
#endif // _BIN_TREE_QUIET_VERIFY

#ifdef _BIN_TREE_DEBUG
    #define _DEBUG_CHECK(condition)                                 \
    {                                                               \
        if (condition)                                              \
        {                                                           \
            _QUIET(ColoredPrintf(RED, GET_NAME(condition) "\n"));   \
            return false;                                           \
        }                                                           \
    }
#else
    #define _DEBUG_CHECK(condition) 
#endif // _BIN_TREE_DEBUG

static bool BinTreeVerify(binTree_t binTree)
{
    _DEBUG_CHECK(binTree            == NULL);
    _DEBUG_CHECK(binTree->root      == NULL);
    _DEBUG_CHECK(binTree->Compare   == NULL);
    _DEBUG_CHECK(binTree->valueSize == 0);

    return true;
}


static bool ValuePtrVerify(void* valuePtr)
{
    _DEBUG_CHECK(valuePtr == NULL)

    return true;
}

#undef _QUIETE
#undef _DEBUG_CHECK

