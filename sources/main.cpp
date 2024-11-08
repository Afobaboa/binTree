#include "binTree.h"
#include "binTreeDumper.h"


//--------------------------------------------------------------------------------------------------


static int Compare(void* firstNum, void* secondNum);
static void PrintValue(FILE* file, void* valuePtr);


int main()
{
    binTree_t binTree = NULL;
    BIN_TREE_INIT(&binTree, sizeof(int), Compare);
    BinTreeDumper dumper = {};
    BIN_TREE_DUMPER_INIT(&dumper, "dump.dot", "dump.png");

    #define DUMP BIN_TREE_DUMP(&dumper, binTree, PrintValue)
    DUMP;

    int value = 2;
    BinTreeInsert(binTree, &value);

    value = 1;
    BinTreeInsert(binTree, &value);

    value = 3;
    BinTreeInsert(binTree, &value);

    DUMP;
    #undef DUMP


    BIN_TREE_DUMPER_DELETE(&dumper);
    BinTreeDelete(&binTree);
    return 0;
}


static int Compare(void* firstNum, void* secondNum)
{
    return *((int*) firstNum) - *((int*) secondNum);
}


static void PrintValue(FILE* file, void* valuePtr)
{
    int value = *((int*) valuePtr);
    fprintf(file, "%d", value);
}
