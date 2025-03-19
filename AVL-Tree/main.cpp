#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "AVLTree.h"

int main()
{
    AVLTree *Root = nullptr;

    // for (int i = 0; i < 5; i++)
    // {
    //     InsertNode(&Root, i);
    // }
    // InsertNode(&Root, 50);
    // InsertNode(&Root, 30);
    // InsertNode(&Root, 70);
    // InsertNode(&Root, 40);
    // InsertNode(&Root, 10);
    // InsertNode(&Root, 80);

    InsertNode(&Root, 10);
    InsertNode(&Root, 20);
    InsertNode(&Root, 30);
    InsertNode(&Root, 40);
    InsertNode(&Root, 50);
    InsertNode(&Root, 60);
    InsertNode(&Root, 70);

    TreeDumpDot(Root);
    DeleteNode(&Root, 60);
    TreeDumpDot(Root);

    TreeTraversal(Root);
    printf("\n");
}
