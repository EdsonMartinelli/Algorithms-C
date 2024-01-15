#include <stdio.h>
#include "../headers/binarytree.h"

static void search(BinaryTree, void *, BinaryTreeNode **, BinaryTreeNode **);
static void getMin(BinaryTreeNode **, BinaryTreeNode **);
static void getMax(BinaryTreeNode **, BinaryTreeNode **);
static BinaryTreeNode *verifyRemoveCondition(BinaryTree *, BinaryTreeNode **, BinaryTreeNode **);
static BinaryTreeNode *removeNodeZeroChildren(BinaryTree *, BinaryTreeNode **, BinaryTreeNode **);
static BinaryTreeNode *removeNodeOneChildren(BinaryTree *, BinaryTreeNode **, BinaryTreeNode **);
static BinaryTreeNode *removeNodeTwoChildren(BinaryTree *, BinaryTreeNode **, BinaryTreeNode **);

void initBinaryTree(BinaryTree *bt, int (*comparator)(void *a, void *b))
{
    *bt = (BinaryTree){.root = NULL, .size = 0, .comparator = comparator};
}

BinaryTreeNode *insertBinaryTree(BinaryTree *bt, BinaryTreeNode *node)
{
    if (node == NULL || bt == NULL)
        return NULL;

    node->left = NULL;
    node->right = NULL;

    if (isBinaryTreeEmpty(*bt))
    {
        bt->root = node;
        bt->size++;
        return node;
    }

    BinaryTreeNode *root = bt->root;
    bool isInserted = false;
    while (!isInserted)
    {
        if ((*bt->comparator)(root->content, node->content) > 0)
        {
            if (root->left == NULL)
            {
                root->left = node;
                isInserted = true;
            }
            else
                root = root->left;
        }
        else
        {
            if (root->right == NULL)
            {
                root->right = node;
                isInserted = true;
            }
            else
                root = root->right;
        }
    }
    bt->size++;
    return node;
}

bool isBinaryTreeEmpty(BinaryTree bt)
{
    if (bt.root == NULL && bt.size == 0)
        return true;
    return false;
}

static void getMin(BinaryTreeNode **nodeFather, BinaryTreeNode **nodeTarget)
{
    if (*nodeTarget == NULL)
        return;

    if ((*nodeTarget)->left == NULL)
        return;

    *(nodeFather) = *nodeTarget;
    *(nodeTarget) = (*nodeTarget)->left;
    getMin(nodeFather, nodeTarget);
}

BinaryTreeNode *getMinBinaryTree(BinaryTree bt)
{
    if (isBinaryTreeEmpty(bt))
        return NULL;

    BinaryTreeNode *nodeFather = NULL;
    BinaryTreeNode *nodeTarget = bt.root;

    getMin(&nodeFather, &nodeTarget);
    return nodeTarget;
}

static void getMax(BinaryTreeNode **nodeFather, BinaryTreeNode **nodeTarget)
{
    if (*nodeTarget == NULL)
        return;

    if ((*nodeTarget)->right == NULL)
        return;

    *(nodeFather) = *nodeTarget;
    *(nodeTarget) = (*nodeTarget)->right;
    getMax(nodeFather, nodeTarget);
}

BinaryTreeNode *getMaxBinaryTree(BinaryTree bt)
{
    if (isBinaryTreeEmpty(bt))
        return NULL;

    BinaryTreeNode *nodeFather = NULL;
    BinaryTreeNode *nodeTarget = bt.root;

    getMax(&nodeFather, &nodeTarget);
    return nodeTarget;
}

static void search(
    BinaryTree bt,
    void *target,
    BinaryTreeNode **nodeFather,
    BinaryTreeNode **nodeTarget)
{

    if (*nodeTarget == NULL)
        return;

    int comp = (*bt.comparator)((*nodeTarget)->content, target);

    if (comp == 0)
        return;

    *nodeFather = *nodeTarget;

    if (comp > 0)
    {
        *(nodeTarget) = (*nodeTarget)->left;
        search(bt, target, nodeFather, nodeTarget);
    }
    else
    {
        *(nodeTarget) = (*nodeTarget)->right;
        search(bt, target, nodeFather, nodeTarget);
    }
}

BinaryTreeNode *searchBinaryTree(BinaryTree bt, void *target)
{
    if (isBinaryTreeEmpty(bt))
        return NULL;

    BinaryTreeNode *nodeFather = NULL;
    BinaryTreeNode *nodeTarget = bt.root;

    search(bt, target, &nodeFather, &nodeTarget);
    return nodeTarget;
}

static BinaryTreeNode *verifyRemoveCondition(
    BinaryTree *bt,
    BinaryTreeNode **nodeFather,
    BinaryTreeNode **nodeTarget)
{
    if ((*nodeTarget)->left == NULL && (*nodeTarget)->right == NULL)
        return removeNodeZeroChildren(bt, nodeFather, nodeTarget);

    if ((*nodeTarget)->left == NULL || (*nodeTarget)->right == NULL)
        return removeNodeOneChildren(bt, nodeFather, nodeTarget);

    return removeNodeTwoChildren(bt, nodeFather, nodeTarget);
}

static BinaryTreeNode *removeNodeZeroChildren(
    BinaryTree *bt,
    BinaryTreeNode **nodeFather,
    BinaryTreeNode **nodeTarget)
{
    if (*nodeFather == NULL && *nodeTarget == bt->root)
    {
        bt->root = NULL;
        return *nodeTarget;
    }

    if ((*nodeFather)->left == *nodeTarget)
        (*nodeFather)->left = NULL;

    if ((*nodeFather)->right == *nodeTarget)
        (*nodeFather)->right = NULL;

    return *nodeTarget;
}

static BinaryTreeNode *removeNodeOneChildren(
    BinaryTree *bt,
    BinaryTreeNode **nodeFather,
    BinaryTreeNode **nodeTarget)
{

    BinaryTreeNode *child = (*nodeTarget)->left == NULL ? (*nodeTarget)->right : (*nodeTarget)->left;

    if (*nodeFather == NULL && *nodeTarget == bt->root)
    {
        bt->root = child;
        return *nodeTarget;
    }

    if ((*nodeFather)->left == *nodeTarget)
        (*nodeFather)->left = child;

    if ((*nodeFather)->right == *nodeTarget)
        (*nodeFather)->right = child;

    return *nodeTarget;
}

static BinaryTreeNode *removeNodeTwoChildren(
    BinaryTree *bt,
    BinaryTreeNode **nodeFather,
    BinaryTreeNode **nodeTarget)
{
    BinaryTreeNode *nodeLocalFather = *nodeTarget;
    BinaryTreeNode *nodeLocalTarget = (*nodeTarget)->left;
    getMax(&nodeLocalFather, &nodeLocalTarget);
    BinaryTreeNode *removedNode = verifyRemoveCondition(bt,
                                                        &nodeLocalFather,
                                                        &nodeLocalTarget);
    removedNode->left = (*nodeTarget)->left;
    removedNode->right = (*nodeTarget)->right;

    if (*nodeFather == NULL && *nodeTarget == bt->root)
    {
        bt->root = removedNode;
        return *nodeTarget;
    }

    if ((*nodeFather)->left == *nodeTarget)
        (*nodeFather)->left = removedNode;

    if ((*nodeFather)->right == *nodeTarget)
        (*nodeFather)->right = removedNode;

    return *nodeTarget;
}

BinaryTreeNode *removeBinaryTree(BinaryTree *bt, void *target)
{
    if (isBinaryTreeEmpty(*bt))
        return NULL;

    BinaryTreeNode *nodeFather = NULL;
    BinaryTreeNode *nodeTarget = bt->root;

    search(*bt, target, &nodeFather, &nodeTarget);

    if (nodeTarget == NULL)
        return NULL;

    BinaryTreeNode *removedNode = verifyRemoveCondition(bt, &nodeFather, &nodeTarget);
    bt->size--;
    return removedNode;
}

static void printBinaryTreeNode(BinaryTreeNode *node, int level)
{
    if (node == NULL)
        return;
    printf("Level[%i]: %i   ", level, *(int *)node->content);
    printBinaryTreeNode(node->left, level + 1);
    printBinaryTreeNode(node->right, level + 1);
}

void printBinaryTree(BinaryTree bt)
{
    printBinaryTreeNode(bt.root, 0);
    printf("\n");
}
