#ifndef _HAVLTREE
#define _HAVLTREE

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef int elem_t;

enum Color
{
    RED   = 1,
    BLACK = 2,
};

typedef struct RBTree
{
    elem_t value;
    Color color;
    struct RBTree *left;
    struct RBTree *right;
    struct RBTree *parent;
} RBTree;

typedef enum
{
    OK                  = 0x000000,
    ALLOC_ERR           = 0x000001,
    NODE_NULLPTR        = 0x000002,
    REPEAT_ELEM         = 0x000004,
    FILE_NOT_OPEN       = 0x000008,
} TreeErrors;

TreeErrors CreateNode(RBTree** Node, elem_t value);
TreeErrors FreeTree(RBTree** Node);
TreeErrors InsertNode(RBTree **Root, elem_t value);
RBTree* NodeFind(RBTree* Root, elem_t value);
TreeErrors TreeTraversal(RBTree* Node);
TreeErrors DeleteNode(RBTree **Root, elem_t value);

TreeErrors LeftRotate(RBTree **Root, RBTree *Node);
TreeErrors RightRotate(RBTree **Root, RBTree *Node);
TreeErrors FixInsertion(RBTree **Root, RBTree *Node);

TreeErrors TreeDumpDot(RBTree* Root);
int GenerateGraph(RBTree *Node, char* buffer, int* buffer_len, const size_t BUFFER_SIZE);

#endif // _HAVLTREE
