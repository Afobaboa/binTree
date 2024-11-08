#ifndef BIN_TREE_DUMPER_H
#define BIN_TREE_DUMPER_H


//--------------------------------------------------------------------------------------------------

#include "binTree.h"
#include "binTreeStructs.h"


struct BinTreeDumper
{
    char*  dotDumpFileName;
    char*  pngDumpFileName;
    FILE*  dotDumpFile;
    size_t dumpCount;
};


bool BinTreeDumperInit(BinTreeDumper* dumper, const char* dotDumpFileName, 
                                              const char* pngDumpFileName);

void BinTreeDumperDelete(BinTreeDumper* dumper);
void BinTreeDump(BinTreeDumper* dumper, binTree_t binTree, Place dumpPlace);


#ifdef _BIN_TREE_DEBUG
    #define BIN_TREE_DUMPER_INIT(dumper, dotDumpFileName, pngDumpFileName) \
        BinTreeDumperInit(dumper, dotDumpFileName, pngDumpFileName)
    
    #define BIN_TREE_DUMPER_DELETE(dumper) \
        BinTreeDumperDelete(dumper)

    #define BIN_TREE_DUMP(dumper, binTree) \
        BinTreeDump(dumper, binTree, GET_PLACE())

#else
    #define BIN_TREE_DUMPER_INIT(dumper, dotDumpFileName, pngDumpFileName) 
    #define BIN_TREE_DUMPER_DELETE(dumper) 
    #define BIN_TREE_DUMP(dumper, binTree) 
#endif // _BIN_TREE_DEBUG


//--------------------------------------------------------------------------------------------------


#endif // BIN_TREE_DUMPER_H