#include "AVLTree.h"

//TODO: написать функцию удаления элемента для обоих деревьев

TreeErrors CreateNode(AVLTree** Node, elem_t value)
{
    *Node = (AVLTree*)calloc(1, sizeof(AVLTree));
    if (*Node == nullptr) return ALLOC_ERR;

    (*Node)->value = value;
    (*Node)->left = nullptr;
    (*Node)->right = nullptr;
    (*Node)->height = 1;

    return OK;
}

TreeErrors FreeTree(AVLTree** Node)
{
    if (*Node == nullptr) return OK;

    FreeTree(&((*Node)->left));
    FreeTree(&((*Node)->right));

    free(*Node);
    *Node = nullptr;

    return OK;
}

int GetHeight(AVLTree* Node)
{
    return Node ? Node->height : 0;
}

int GetBalanceFactor(AVLTree* Node)
{
    return Node ? GetHeight(Node->left) - GetHeight(Node->right) : 0;
}

TreeErrors UpdateHeight(AVLTree* Node)
{
    if (Node == nullptr) return NODE_NULLPTR;

    Node->height = 1 + (GetHeight(Node->left) > GetHeight(Node->right) ?
                        GetHeight(Node->left) : GetHeight(Node->right));

    return OK;
}

TreeErrors RightRotate(AVLTree **Root)
{
    if ((*Root) == nullptr || (*Root)->left == nullptr) return NODE_NULLPTR;

    AVLTree *NewRoot = (*Root)->left;
    (*Root)->left = NewRoot->right;
    NewRoot->right = *Root;

    UpdateHeight(*Root);
    UpdateHeight(NewRoot);

    *Root = NewRoot;

    return OK;
}

TreeErrors LeftRotate(AVLTree **Root)
{
    if ((*Root) == nullptr || (*Root)->right == nullptr) return NODE_NULLPTR;

    AVLTree *NewRoot = (*Root)->right;
    (*Root)->right = NewRoot->left;
    NewRoot->left = *Root;

    UpdateHeight(*Root);
    UpdateHeight(NewRoot);

    *Root = NewRoot;

    return OK;
}

TreeErrors InsertNode(AVLTree **Root, elem_t value)
{
    if (*Root == nullptr)
    {
        return CreateNode(Root, value);
    }

    if (value < (*Root)->value)
    {
        TreeErrors err = InsertNode(&((*Root)->left), value);
        if (err != OK) return err;
    }
    else if (value > (*Root)->value)
    {
        TreeErrors err = InsertNode(&((*Root)->right), value);
        if (err != OK) return err;
    }
    else
    {
        return REPEAT_ELEM;
    }

    UpdateHeight(*Root);

    int balance = GetBalanceFactor(*Root);

    if (balance > 1 && value < (*Root)->left->value)
    {
        return RightRotate(Root);
    }

    if (balance < -1 && value > (*Root)->right->value)
    {
        return LeftRotate(Root);
    }

    if (balance > 1 && value > (*Root)->left->value)
    {
        TreeErrors err = LeftRotate(&((*Root)->left));
        if (err != OK) return err;
        return RightRotate(Root);
    }

    if (balance < -1 && value < (*Root)->right->value)
    {
        TreeErrors err = RightRotate(&((*Root)->right));
        if (err != OK) return err;
        return LeftRotate(Root);
    }

    return OK;
}

TreeErrors DeleteNode(AVLTree **Root, elem_t value)
{
    if (*Root == nullptr)   return NODE_NULLPTR;


    if      (value < (*Root)->value)  return DeleteNode(&((*Root)->left),  value);
    else if (value > (*Root)->value)  return DeleteNode(&((*Root)->right), value);

    else
    {
        if ((*Root)->left == nullptr)
        {
            AVLTree *temp = *Root;
            *Root = (*Root)->right;
            free(temp);
            temp = nullptr;
        }
        else if ((*Root)->right == nullptr)
        {
            AVLTree *temp = *Root;
            *Root = (*Root)->left;
            free(temp);
            temp = nullptr;
        }
        else
        {
            AVLTree *minNode = (*Root)->right;
            while (minNode->left != nullptr)
            {
                minNode = minNode->left;
            }

            (*Root)->value = minNode->value;
            return DeleteNode(&((*Root)->right), minNode->value);
        }
    #if 0
        else
        {
            AVLTree *maxNode = (*Root)->left;
            while (maxNode->right != nullptr)
            {
                maxNode = maxNode->right;
            }
            (*Root)->value = maxNode->value;
            return DeleteNode(&((*Root)->left), maxNode->value);
        }
    #endif
    }

    return OK;
}

TreeErrors TreeTraversal(AVLTree *Node)
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
