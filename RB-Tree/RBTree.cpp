#include "RBTree.h"

TreeErrors CreateNode(RBTree **Node, elem_t value)
{
    *Node = (RBTree*)calloc(1, sizeof(RBTree));

    if (*Node == nullptr)
    {
        return ALLOC_ERR;
    }

    (*Node)->value = value;
    (*Node)->color = RED;
    (*Node)->left = nullptr;
    (*Node)->right = nullptr;
    (*Node)->parent = nullptr;

    return OK;
}

TreeErrors FreeTree(RBTree **Node)
{
    if (*Node == nullptr) return OK;

    FreeTree(&((*Node)->left));
    FreeTree(&((*Node)->right));

    free(*Node);
    *Node = nullptr;

    return OK;
}

TreeErrors LeftRotate(RBTree **Root, RBTree *Node)
{
    RBTree *Right = Node->right;
    Node->right = Right->left;

    if (Right->left)
        Right->left->parent = Node;

    Right->parent = Node->parent;

    if (!Node->parent)
        *Root = Right;
    else if (Node == Node->parent->left)
        Node->parent->left = Right;
    else
        Node->parent->right = Right;

    Right->left = Node;
    Node->parent = Right;

    return OK;
}

TreeErrors RightRotate(RBTree **Root, RBTree *Node)
{
    RBTree *Left = Node->left;
    Node->left = Left->right;

    if (Left->right) Left->right->parent = Node;

    Left->parent = Node->parent;

    if (!Node->parent)
        *Root = Left;
    else if (Node == Node->parent->left)
        Node->parent->left = Left;
    else
        Node->parent->right = Left;

    Left->right = Node;
    Node->parent = Left;

    return OK;
}

TreeErrors FixInsertion(RBTree **Root, RBTree *Node)
{
    while (Node->parent && Node->parent->color == RED)
    {
        RBTree *Grandparent = Node->parent->parent;
        if (Node->parent == Grandparent->left)
        {
            RBTree *Uncle = Grandparent->right;
            if (Uncle && Uncle->color == RED)
            { // Uncle RED ---> repaint
                Grandparent->color = RED;
                Node->parent->color = BLACK;
                Uncle->color = BLACK;
                Node = Grandparent;
            }
            else
            { // Uncle BLACK
                if (Node == Node->parent->right)
                { // LR
                    Node = Node->parent;
                    LeftRotate(Root, Node);
                }
                // LL
                Node->parent->color = BLACK;
                Grandparent->color = RED;
                RightRotate(Root, Grandparent);
            }
        }
        else
        {
            RBTree *Uncle = Grandparent->left;
            if (Uncle && Uncle->color == RED)
            {
                Grandparent->color = RED;
                Node->parent->color = BLACK;
                Uncle->color = BLACK;
                Node = Grandparent;
            }
            else
            {
                if (Node == Node->parent->left)
                {
                    Node = Node->parent;
                    RightRotate(Root, Node);
                }
                Node->parent->color = BLACK;
                Grandparent->color = RED;
                LeftRotate(Root, Grandparent);
            }
        }
    }

    (*Root)->color = BLACK;

    return OK;
}

TreeErrors InsertNode(RBTree **Root, elem_t value)
{
    RBTree *NewNode;

    TreeErrors err = CreateNode(&NewNode, value);
    if (err != OK)
        return err;

    RBTree *Parent = nullptr, *Current = *Root;

    while (Current != nullptr)
    {
        Parent = Current;
        if (value < Current->value)
            Current = Current->left;
        else
            Current = Current->right;
    }

    NewNode->parent = Parent;

    if (Parent == nullptr)
    {
        *Root = NewNode;
    }
    else if (value < Parent->value)
    {
        Parent->left = NewNode;
    }
    else
    {
        Parent->right = NewNode;
    }

    FixInsertion(Root, NewNode);

    return OK;
}

RBTree* NodeFind(RBTree *Root, elem_t value)
{
    if (Root == nullptr)       return nullptr;

    if (value == Root->value)  return Root;
    if (value <  Root->value)  return NodeFind(Root->left,  value);
    else                       return NodeFind(Root->right, value);

    return nullptr;
}

TreeErrors TreeTraversal(RBTree *Node)
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

TreeErrors DeleteNode(RBTree **Root, elem_t value)
{
    if (*Root == nullptr)   return NODE_NULLPTR;


    if      (value < (*Root)->value)  return DeleteNode(&((*Root)->left),  value);
    else if (value > (*Root)->value)  return DeleteNode(&((*Root)->right), value);

    else
    {
        if ((*Root)->left == nullptr)
        {
            RBTree *temp = *Root;
            *Root = (*Root)->right;
            free(temp);
            temp = nullptr;
        }
        else if ((*Root)->right == nullptr)
        {
            RBTree *temp = *Root;
            *Root = (*Root)->left;
            free(temp);
            temp = nullptr;
        }
        else
        {
            RBTree *minNode = (*Root)->right;
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
            RBTree *maxNode = (*Root)->left;
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
