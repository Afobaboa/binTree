#ifndef BIN_TREE_H
#define BIN_TREE_H


//--------------------------------------------------------------------------------------------------


#include <stddef.h>

#include "logPrinter.h"


// #define _BIN_TREE_DEBUG
#ifdef _BIN_TREE_DEBUG
    #define _BIN_TREE_ON_DEBUG(...) __VA_ARGS__
#else
    #define _BIN_TREE_ON_DEBUG(...) 
#endif // _BIN_TREE_ON_DEBUG


struct BinTree;
typedef BinTree* binTree_t;


typedef int (*comparator_t)(void* firstElemPtr, void* secondElemPtr);

bool BinTreeInit(binTree_t* binTree, const size_t valueSize, comparator_t Compare
                                                _BIN_TREE_ON_DEBUG(, VariableInitInfo initInfo));
                
#define BIN_TREE_INIT(binTree, valueSize, Compare) \
    BinTreeInit(binTree, valueSize, Compare _BIN_TREE_ON_DEBUG(, GET_VARIABLE_INIT_INFO(binTree)))


void BinTreeDelete(binTree_t* binTree);

bool BinTreeInsert(binTree_t binTree, void* valuePtr);


//--------------------------------------------------------------------------------------------------


#endif // BIN_TREE_H