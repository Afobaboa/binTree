#include "binTree.h"
#include "binTreeDumper.h"


//--------------------------------------------------------------------------------------------------


int Compare(void* firstNum, void* secondNum);


int main()
{
    binTree_t binTree = NULL;
    BIN_TREE_INIT(&binTree, sizeof(int), &Compare);
    BinTreeDumper dumper = {};
    BIN_TREE_DUMPER_INIT(&dumper, "dump.dot", "dump.png");

    BIN_TREE_DUMP(&dumper, binTree);

    BIN_TREE_DUMPER_DELETE(&dumper);
    BinTreeDelete(&binTree);
    return 0;
}


int Compare(void* firstNum, void* secondNum)
{
    return *((int*) firstNum) - *((int*) secondNum);
}