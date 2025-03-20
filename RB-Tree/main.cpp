#include "RBTree.h"

int main()
{
    RBTree *Root = nullptr;

    for (int i = 1; i <= 7; i++)
    {
        InsertNode(&Root, i * 100);
    }

    //InsertNode(&Root, 1);
    TreeDumpDot(Root);

    for (int i = 1; i <= 7; i++)
    {
        InsertNode(&Root, i * 10);
    }
    TreeDumpDot(Root);

//     DeleteNode(&Root, 60);
//     TreeDumpDot(Root);
//
//     DeleteNode(&Root, 70);
//     TreeDumpDot(Root);
//
//     DeleteNode(&Root, 50);
//     TreeDumpDot(Root);

    TreeTraversal(Root);
    printf("\n");

    FreeTree(&Root);
}
