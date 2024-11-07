#include <stdio.h>
#include <stdlib.h>

#include "binTreeDumper.h"


//--------------------------------------------------------------------------------------------------


static void PrintDigraphEnvironment(BinTreeDumper* dumper);

static void PrintSubgraphHeader(BinTreeDumper* dumper);
static void PrintSubgraphEnding(BinTreeDumper* dumper);

static void PrintBinTree(BinTreeDumper* dumper, binTree_t binTree, VariableInitInfo* variableInfo);

static void MakeGraph(BinTreeDumper* dumper);


//--------------------------------------------------------------------------------------------------


bool BinTreeDumperInit(BinTreeDumper* dumper, const char* dotDumpFileName, 
                                              const char* pngDumpFileName)
{
    static bool isInit = false;
    if (isInit)
        return false;
    
    dumper->dotDumpFile = fopen(dotDumpFileName, "w");
    if (dumper->dotDumpFile == NULL)
        return false;

    PrintDigraphEnvironment(dumper);

    dumper->dotDumpFileName = (char*) dotDumpFileName;
    dumper->pngDumpFileName = (char*) pngDumpFileName;
    dumper->dumpCount       = 0;

    isInit = true;
    return true; 
}


void BinTreeDumperDelete(BinTreeDumper* dumper)
{
    fclose(dumper->dotDumpFile);
    dumper->dotDumpFile = NULL;
}


void BinTreeDump(BinTreeDumper* dumper, binTree_t binTree, VariableInitInfo variableInfo)
{
    PrintSubgraphHeader(dumper);
    PrintBinTree(dumper, binTree, &variableInfo);
    PrintSubgraphEnding(dumper);

    MakeGraph(dumper);
    getchar();  // pause
    
    dumper->dumpCount++;
}


//--------------------------------------------------------------------------------------------------


static void PrintDigraphEnvironment(BinTreeDumper* dumper)
{
    fprintf(dumper->dotDumpFile, "digraph dumpGraph\n"
                                 "{\n"
                                 "\trankdir = LR; \n");
}


static void PrintSubgraphHeader(BinTreeDumper* dumper)
{

}


static void PrintSubgraphEnding(BinTreeDumper* dumper)
{

}


static void PrintBinTree(BinTreeDumper* dumper, binTree_t binTree, VariableInitInfo* variableInfo)
{

}


static void MakeGraph(BinTreeDumper* dumper)
{
    const size_t maxCommandLength = 100;
    char commandForDot[maxCommandLength + 1] = {};
    if (sprintf(commandForDot, "dor -Tpng %s -o %s\n", 
                dumper->dotDumpFileName, dumper->pngDumpFileName) >= maxCommandLength)
    {
        ColoredPrintf(RED, "commandForDot is overflowed\n");
        return;
    }

    fflush(dumper->dotDumpFile);
    system(commandForDot);
}
