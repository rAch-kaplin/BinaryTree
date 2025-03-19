#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "AVLTree.h"

int main()
{
    AVLTree *Root = nullptr;

    for (int i = 1; i <= 7; i++)
    {
        InsertNode(&Root, i * 10);
    }
    // InsertNode(&Root, 50);
    // InsertNode(&Root, 30);
    // InsertNode(&Root, 70);
    // InsertNode(&Root, 40);
    // InsertNode(&Root, 10);
    // InsertNode(&Root, 80);

    TreeDumpDot(Root);
    DeleteNode(&Root, 60);
    DeleteNode(&Root, 70);
    DeleteNode(&Root, 50);
    TreeDumpDot(Root);

    TreeTraversal(Root);
    printf("\n");
}
