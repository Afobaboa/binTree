#ifndef BINARY_TREE_H
#define BINARY_TREE_H


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


typedef int (*comparator_t)(void* firstElemPtr, void* secondElemPtr);

bool BinTreeInit(BinTree** binTree, const size_t valueSize, comparator_t* Compare
                                                _BIN_TREE_ON_DEBUG(, VariableInitInfo initInfo));
                
#define BIN_TREE_INIT(binTree, valueSize, Compare) \
    BinTreeInit(binTree, valueSize, Compare        \
                                    _BIN_TREE_ON_DEBUG(, GET_VARIABLE_INIT_INFO(binTree)))


void BinTreeDelete(BinTree** binTree);


//--------------------------------------------------------------------------------------------------


#endif // BINARY_TREE_H