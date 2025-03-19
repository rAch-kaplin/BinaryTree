#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "AVLTree.h"

int main()
{
    //LoggerInit(LOGL_DEBUG, "logfile.log", DEFAULT_MODE);
    AVLTree *Root = nullptr;

    for (int i = 1; i <= 7; i++)
    {
        InsertNode(&Root, i * 10);
    }

    InsertNode(&Root, 1);
    TreeDumpDot(Root);

    DeleteNode(&Root, 60);
    TreeDumpDot(Root);

    DeleteNode(&Root, 70);
    TreeDumpDot(Root);
    
    DeleteNode(&Root, 50);
    //RightRotate(&Root);
    TreeDumpDot(Root);

    TreeTraversal(Root);
    printf("\n");
    //LoggerDeinit();
}
