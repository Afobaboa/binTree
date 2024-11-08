#include "binTree.h"
#include "binTreeDumper.h"


//--------------------------------------------------------------------------------------------------


static int Compare(const void* firstNum, const void* secondNum);
static void PrintValue(FILE* file, const void* valuePtr);


int main()
{
    binTree_t binTree = NULL;
    int value = -5;
    BIN_TREE_INIT(&binTree, sizeof(int), &value, Compare);
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


static int Compare(const void* firstNum, const void* secondNum)
{
    return *((const int*) firstNum) - *((const int*) secondNum);
}


static void PrintValue(FILE* file, const void* valuePtr)
{
    int value = *((const int*) valuePtr);
    fprintf(file, "%d", value);
}
