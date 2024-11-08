#include <stdio.h>
#include <stdlib.h>

#include "binTreeDumper.h"


//--------------------------------------------------------------------------------------------------


static void PrintDigraphEnvironment(BinTreeDumper* dumper);

static void PrintSubgraphHeader(BinTreeDumper* dumper);
static void PrintSubgraphEnding(BinTreeDumper* dumper);

static void PrintBinTree(BinTreeDumper* dumper, binTree_t binTree, valuePrinter_t PrintValue, 
                         Place* dumpPlace);

static void DeclareBinTreeHeader(BinTreeDumper* dumper, binTree_t binTree, Place* dumpPlace);
static void DeclareBinTreeNodes(BinTreeDumper* dumper, BinTreeNode* node, valuePrinter_t PrintValue, 
                                const size_t rank);

static void ConnectBinTreeHeader(BinTreeDumper* dumper, binTree_t binTree);
static void ConnectBinTreeNodes(BinTreeDumper* dumper, BinTreeNode* node);

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


void BinTreeDump(BinTreeDumper* dumper, binTree_t binTree, valuePrinter_t PrintValue, 
                 Place dumpPlace)
{
    PrintSubgraphHeader(dumper);
    PrintBinTree(dumper, binTree, PrintValue, &dumpPlace);
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
                                 "\trankdir = HD; \n");
}


static void PrintSubgraphHeader(BinTreeDumper* dumper)
{
    fseek(dumper->dotDumpFile, -2, SEEK_END);
        
    fprintf(dumper->dotDumpFile, "\n\tsubgraph dump%zu\n"
                                 "\t{\n"
                                 "\t\trankdir = HD;\n",
                                 dumper->dumpCount);
}


static void PrintSubgraphEnding(BinTreeDumper* dumper)
{
    fprintf(dumper->dotDumpFile, "\t}\n"
                                 "}");
}


static void PrintBinTree(BinTreeDumper* dumper, binTree_t binTree, valuePrinter_t PrintValue, 
                         Place* dumpPlace)
{
    DeclareBinTreeHeader(dumper, binTree, dumpPlace);
    DeclareBinTreeNodes(dumper, binTree->root, PrintValue, 0);

    ConnectBinTreeHeader(dumper, binTree);
    ConnectBinTreeNodes(dumper, binTree->root);
}


static void MakeGraph(BinTreeDumper* dumper)
{
    const size_t maxCommandLength = 100;
    char commandForDot[maxCommandLength + 1] = {};
    if (sprintf(commandForDot, "dot -Tpng %s -o %s\n", 
                dumper->dotDumpFileName, dumper->pngDumpFileName) >= (int) maxCommandLength)
    {
        ColoredPrintf(RED, "commandForDot is overflowed\n");
        return;
    }

    fflush(dumper->dotDumpFile);
    system(commandForDot);
}


static void DeclareBinTreeHeader(BinTreeDumper* dumper, binTree_t binTree, Place* dumpPlace)
{
    fprintf(dumper->dotDumpFile, "\t\tTreeHeader%zu[color=red, shape=record, label=\""
                                 "{ dumpCount   | %zu   } | "
                                 "{ dumpPlace   | %s:%d } | "
                                 "{ valueSize   | %zu   } | "
                                 "{ rootAddress | %p    }",
                                 dumper->dumpCount,
                                 dumper->dumpCount,
                                 dumpPlace->file, dumpPlace->line,
                                 binTree->valueSize,
                                 binTree->root);

    #ifdef _BIN_TREE_DEBUG
    fprintf(dumper->dotDumpFile, " | { treeName      | %s    } | "
                                 "   { treeInitPlace | %s:%d }",
                                 binTree->initInfo.name,
                                 binTree->initInfo.place.file, binTree->initInfo.place.line);
    #endif // _BIN_TREE_DEBUG

    fprintf(dumper->dotDumpFile, "\"];\n\n");
}


static void DeclareBinTreeNodes(BinTreeDumper* dumper, BinTreeNode* node, valuePrinter_t PrintValue, 
                                const size_t rank)
{
    if (node->leftNode != NULL)
        DeclareBinTreeNodes(dumper, node->leftNode, PrintValue, rank + 1);

    if (node->rightNode != NULL)
        DeclareBinTreeNodes(dumper, node->rightNode, PrintValue, rank + 1);

    fprintf(dumper->dotDumpFile, "\t\tnode%p_%zu[shape=record, rank=%zu, label=\""
                                 "{ value | ",
                                 node, dumper->dumpCount, rank);

    PrintValue(dumper->dotDumpFile, node->valuePtr);

    fprintf(dumper->dotDumpFile, "} | "
                                 "{ leftNode  | %p } | "
                                 "{ rightNode | %p }\"];\n",
                                 node->leftNode, 
                                 node->rightNode);
}


static void ConnectBinTreeHeader(BinTreeDumper* dumper, binTree_t binTree)
{
    fprintf(dumper->dotDumpFile, "\t\tTreeHeader%zu -> node%p_%zu;\n\n",
                                 dumper->dumpCount, binTree->root, dumper->dumpCount);
}


static void ConnectBinTreeNodes(BinTreeDumper* dumper, BinTreeNode* node)
{
    if (node->leftNode != NULL)
    {
        fprintf(dumper->dotDumpFile, "node%p_%zu -> node%p_%zu;\n",
                                     node, dumper->dumpCount, node->leftNode, dumper->dumpCount);
        ConnectBinTreeNodes(dumper, node->leftNode);
    }

    if (node->rightNode != NULL)
    {
        fprintf(dumper->dotDumpFile, "node%p_%zu -> node%p_%zu;\n",
                                     node, dumper->dumpCount, node->rightNode, dumper->dumpCount);
        ConnectBinTreeNodes(dumper, node->rightNode);
    }
}
