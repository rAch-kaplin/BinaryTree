#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"

int main()
{
    BinaryTree *Root = nullptr;

    InsertNode(&Root, 50);
    InsertNode(&Root, 30);
    InsertNode(&Root, 70);

    printf("Tree Traversal:\n");
    TreeTraversal(Root);

    int search_value = 30;
    BinaryTree *found_node = NodeFind(Root, search_value);
    if (found_node)
    {
        printf("\nFound node with value %d\n", found_node->value);
    }
    else
    {
        printf("\nNode with value %d not found\n", search_value);
    }

    FreeTree(&Root);

}

TreeErrors CreateNode(BinaryTree **Node, elem_t value)
{
    *Node = (BinaryTree*)calloc(1, sizeof(BinaryTree));

    if (*Node == nullptr)
    {
        return ALLOC_ERR;
    }

    (*Node)->value = value;
    (*Node)->left = nullptr;
    (*Node)->right = nullptr;

    return OK;
}

TreeErrors FreeTree(BinaryTree **Node)
{
    if (*Node == nullptr) return OK;

    FreeTree(&((*Node)->left));
    FreeTree(&((*Node)->right));

    free(*Node);
    *Node = nullptr;

    return OK;
}

TreeErrors InsertNode(BinaryTree **Root, elem_t value)
{
    if (*Root == nullptr)
    {
        return CreateNode(Root, value);
    }

    if (value < (*Root)->value)
    {
        return InsertNode(&((*Root)->left), value);
    }
    else
    {
        return InsertNode(&((*Root)->right), value);
    }

    return OK;
}

TreeErrors InsertNodeLoop(BinaryTree **Root, elem_t value)
{
    if (*Root == nullptr)
    {
        return CreateNode(Root, value);
    }

    BinaryTree *cur = *Root; //TODO:(TreeNode)

    while (cur != nullptr)
    {
        if (value < cur->value)
        {
            if (cur->left != nullptr)
            {
                cur = cur->left;
            }
            else
            {
                return CreateNode(&(cur->left), value);
            }
        }
        else
        {
            if (cur->right != nullptr)
            {
                cur = cur->right;
            }
            else
            {
                return CreateNode(&(cur->right), value);
            }
        }
    }

    return OK;
}

TreeErrors InsertNodeLoop2(BinaryTree **Root, elem_t value)
{
    if (! *Root)
    {
        return CreateNode(Root, value);
    }

    BinaryTree *cur = *Root; //TODO:(TreeNode)

    while (cur)
    {
        if (value < cur->value)
        {
            if (cur->left) cur = cur->left;
            else           return CreateNode(&(cur->left), value);
        }

        else
        {
            if (cur->right) cur = cur->right;
            else            return CreateNode(&(cur->right), value);
        }
    }

    return OK;
}

BinaryTree* NodeFind(BinaryTree *Root, elem_t value)
{
    if (Root == nullptr)
    {
        return nullptr;
    }

    if (Root->value == value) return Root;

    if (value < Root->value)
    {
        return NodeFind(Root->left, value);
    }
    else
    {
        return NodeFind(Root->right, value);
    }

    return nullptr;
}

BinaryTree* NodeFind2(BinaryTree *Root, elem_t value)
{
    if (Root == nullptr)       return nullptr;

    if (value == Root->value)  return Root;
    if (value <  Root->value)  return NodeFind(Root->left,  value);
    else                       return NodeFind(Root->right, value);

    return nullptr;
}

TreeErrors TreeTraversal(BinaryTree *Node)
{
    if (Node == nullptr)
    {
        return NODE_NULLPTR;
    }

    TreeTraversal(Node->left);
    printf("%d ", Node->value);
    TreeTraversal(Node->right);

    return OK;
}

//char *str = nullptr;
//scanf("%m[^\n]", &str);
// ...
// ...
// ...
//free(str);
//str = nullptr
