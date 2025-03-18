#ifndef _HTREE
#define _HTREE

typedef int elem_t;

typedef struct BinaryTree
{
    elem_t value;
    struct BinaryTree *left;
    struct BinaryTree *right;
} BinaryTree;

enum TreeErrors
{
    OK                  = 0x000000,
    ALLOC_ERR           = 0x000001,
    NODE_NULLPTR        = 0x000002,
};

TreeErrors CreateNode(BinaryTree **Node, elem_t value);
TreeErrors FreeTree(BinaryTree **Node);
TreeErrors InsertNode(BinaryTree **Root, elem_t value);
BinaryTree* NodeFind(BinaryTree *Root, elem_t value);
BinaryTree* NodeFind2(BinaryTree *Root, elem_t value);
TreeErrors TreeTraversal(BinaryTree *Node);
TreeErrors InsertNodeLoop(BinaryTree **Root, elem_t value);
TreeErrors InsertNodeLoop2(BinaryTree **Root, elem_t value);

#endif // _HTREE
