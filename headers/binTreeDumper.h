#ifndef BIN_TREE_DUMPER_H
#define BIN_TREE_DUMPER_H


//--------------------------------------------------------------------------------------------------

#include <stdio.h>

#include "binTree.h"
#include "binTreeStructs.h"


struct BinTreeDumper
{
    char*  dotDumpFileName;
    char*  pngDumpFileName;
    FILE*  dotDumpFile;
    size_t dumpCount;
};

typedef void (*valuePrinter_t)(FILE* file, void* valuePtr);


bool BinTreeDumperInit(BinTreeDumper* dumper, const char* dotDumpFileName, 
                                              const char* pngDumpFileName);

void BinTreeDumperDelete(BinTreeDumper* dumper);
void BinTreeDump(BinTreeDumper* dumper, binTree_t binTree, valuePrinter_t PrintValue, 
                 Place dumpPlace);


#ifdef _BIN_TREE_DEBUG
    #define BIN_TREE_DUMPER_INIT(dumper, dotDumpFileName, pngDumpFileName) \
        BinTreeDumperInit(dumper, dotDumpFileName, pngDumpFileName)
    
    #define BIN_TREE_DUMPER_DELETE(dumper) \
        BinTreeDumperDelete(dumper)

    #define BIN_TREE_DUMP(dumper, binTree, PrintValue) \
        BinTreeDump(dumper, binTree, PrintValue, GET_PLACE())

#else
    #define BIN_TREE_DUMPER_INIT(dumper, dotDumpFileName, pngDumpFileName) 
    #define BIN_TREE_DUMPER_DELETE(dumper) 
    #define BIN_TREE_DUMP(dumper, binTree, PrintValue) 
#endif // _BIN_TREE_DEBUG


//--------------------------------------------------------------------------------------------------


#endif // BIN_TREE_DUMPER_H