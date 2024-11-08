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

    #define INSERT(val)                 \
    {                                   \
        value = val;                    \
        BinTreeInsert(binTree, &value); \
    }

    #define DELETE(val)                         \
    {                                           \
        value = val;                            \
        BinTreeValueDelete(binTree, &value);    \
    }

    DUMP;
    int value = 0;

    INSERT(2);
    INSERT(1);
    INSERT(3);
    INSERT(-1);

    DUMP;

    DELETE(-1);
    DUMP;

    DELETE(2);
    DUMP;

    DUMP;

    
    #undef DUMP
    #undef INSERT
    #undef DELETE

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
