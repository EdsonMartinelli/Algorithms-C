#include <stdio.h>
#include "../headers/avltree.h"

static int maxHeight(AVLTreeNode);
static AVLTreeNode *insert(AVLTree *, AVLTreeNode *, AVLTreeNode *, AVLTreeNode *);
static void leftRotation(AVLTree *, AVLTreeNode *, AVLTreeNode *);
static void rightRotation(AVLTree *, AVLTreeNode *, AVLTreeNode *);
static void search(AVLTree, void *, AVLTreeNode **, AVLTreeNode **);
static void getMin(AVLTreeNode **, AVLTreeNode **);
static void getMax(AVLTreeNode **, AVLTreeNode **);
static AVLTreeNode *verifyRemoveCondition(AVLTree *, AVLTreeNode **, AVLTreeNode **);
static AVLTreeNode *removeNodeZeroChildren(AVLTree *, AVLTreeNode **, AVLTreeNode **);
static AVLTreeNode *removeNodeOneChildren(AVLTree *, AVLTreeNode **, AVLTreeNode **);
static AVLTreeNode *removeNodeTwoChildren(AVLTree *, AVLTreeNode **, AVLTreeNode **);

void initAVLTree(AVLTree *bt, int (*comparator)(void *a, void *b))
{
    *bt = (AVLTree){.root = NULL, .size = 0, .comparator = comparator};
}

static int maxHeight(AVLTreeNode target)
{
    return target.heightLeft <= target.heightRight ? target.heightRight : target.heightLeft;
}

static void leftRotation(AVLTree *at,
                         AVLTreeNode *nodeFather,
                         AVLTreeNode *nodeTarget)
{
    if (nodeTarget == NULL)
        return;

    AVLTreeNode *tempRight = nodeTarget->right;

    nodeTarget->right = (nodeTarget->right)->left;
    nodeTarget->heightRight = tempRight->heightLeft;

    tempRight->left = nodeTarget;
    tempRight->heightLeft = maxHeight(*nodeTarget) + 1;

    if (nodeFather == NULL)
    {
        at->root = tempRight;
        return;
    }

    if (nodeFather->left == nodeTarget)
        nodeFather->left = tempRight;
    else
        nodeFather->right = tempRight;
}

static void rightRotation(AVLTree *at,
                          AVLTreeNode *nodeFather,
                          AVLTreeNode *nodeTarget)
{
    if (nodeTarget == NULL)
        return;

    AVLTreeNode *tempLeft = nodeTarget->left;
    nodeTarget->left = (nodeTarget->left)->right;
    nodeTarget->heightLeft = tempLeft->heightRight;

    tempLeft->right = nodeTarget;
    tempLeft->heightRight = maxHeight(*nodeTarget) + 1;

    if (nodeFather == NULL)
    {
        at->root = tempLeft;
        return;
    }

    if (nodeFather->left == nodeTarget)
        nodeFather->left = tempLeft;
    else
        nodeFather->right = tempLeft;
}

static AVLTreeNode *insert(AVLTree *at, AVLTreeNode *father, AVLTreeNode *current, AVLTreeNode *node)
{
    if (isAVLTreeEmpty(*at))
    {
        at->root = node;
        return node;
    }

    int comp = (*at->comparator)(current->content, node->content);

    if (comp > 0)
    {
        if (current->left != NULL)
        {
            AVLTreeNode *insertedNode = insert(at, current, current->left, node);
            current->heightLeft = maxHeight(*(current->left)) + 1;
            int balanceFactor = current->heightLeft - current->heightRight;
            if (balanceFactor > 1)
            {
                if ((current->left)->heightLeft < (current->left)->heightRight)
                    leftRotation(at, current, current->left);
                rightRotation(at, father, current);
            }
            return insertedNode;
        }
        current->heightLeft++;
        current->left = node;
        return node;
    }
    else
    {
        if (current->right != NULL)
        {
            AVLTreeNode *insertedNode = insert(at, current, current->right, node);
            current->heightRight = maxHeight(*(current->right)) + 1;
            int balanceFactor = current->heightRight - current->heightLeft;
            if (balanceFactor > 1)
            {
                if ((current->right)->heightLeft > (current->right)->heightRight)
                    rightRotation(at, current, current->right);
                leftRotation(at, father, current);
            }
            return insertedNode;
        }
        current->heightRight++;
        current->right = node;
        return node;
    }
}

AVLTreeNode *insertAVLTree(AVLTree *at, AVLTreeNode *node)
{
    if (node == NULL || at == NULL)
        return NULL;

    node->left = NULL;
    node->right = NULL;
    node->heightLeft = 0;
    node->heightRight = 0;

    AVLTreeNode *insertedNode = insert(at, NULL, at->root, node);
    at->size++;
    return insertedNode;
}

bool isAVLTreeEmpty(AVLTree at)
{
    if (at.root == NULL && at.size == 0)
        return true;
    return false;
}

static void getMin(AVLTreeNode **nodeFather, AVLTreeNode **nodeTarget)
{
    if (*nodeTarget == NULL)
        return;

    if ((*nodeTarget)->left == NULL)
        return;

    *(nodeFather) = *nodeTarget;
    *(nodeTarget) = (*nodeTarget)->left;
    getMin(nodeFather, nodeTarget);
}

AVLTreeNode *getMinAVLTree(AVLTree at)
{
    if (isAVLTreeEmpty(at))
        return NULL;

    AVLTreeNode *nodeFather = NULL;
    AVLTreeNode *nodeTarget = at.root;

    getMin(&nodeFather, &nodeTarget);
    return nodeTarget;
}

static void getMax(AVLTreeNode **nodeFather, AVLTreeNode **nodeTarget)
{
    if (*nodeTarget == NULL)
        return;

    if ((*nodeTarget)->right == NULL)
        return;

    *(nodeFather) = *nodeTarget;
    *(nodeTarget) = (*nodeTarget)->right;
    getMax(nodeFather, nodeTarget);
}

AVLTreeNode *getMaxAVLTree(AVLTree at)
{
    if (isAVLTreeEmpty(at))
        return NULL;

    AVLTreeNode *nodeFather = NULL;
    AVLTreeNode *nodeTarget = at.root;

    getMax(&nodeFather, &nodeTarget);
    return nodeTarget;
}

/*static void search(
    AVLTree at,
    void *target,
    AVLTreeNode **nodeFather,
    AVLTreeNode **nodeTarget)
{

    if (*nodeTarget == NULL)
        return;

    int comp = (*at.comparator)((*nodeTarget)->content, target);

    if (comp == 0)
        return;

    *nodeFather = *nodeTarget;

    if (comp > 0)
    {
        *(nodeTarget) = (*nodeTarget)->left;
        search(at, target, nodeFather, nodeTarget);
    }
    else
    {
        *(nodeTarget) = (*nodeTarget)->right;
        search(at, target, nodeFather, nodeTarget);
    }
}

AVLTreeNode *searchAVLTree(AVLTree at, void *target)
{
    if (isAVLTreeEmpty(at))
        return NULL;

    AVLTreeNode *nodeFather = NULL;
    AVLTreeNode *nodeTarget = at.root;

    search(at, target, &nodeFather, &nodeTarget);
    return nodeTarget;
}

static AVLTreeNode *verifyRemoveCondition(
    AVLTree *at,
    AVLTreeNode **nodeFather,
    AVLTreeNode **nodeTarget)
{
    if ((*nodeTarget)->left == NULL && (*nodeTarget)->right == NULL)
        return removeNodeZeroChildren(at, nodeFather, nodeTarget);

    if ((*nodeTarget)->left == NULL || (*nodeTarget)->right == NULL)
        return removeNodeOneChildren(at, nodeFather, nodeTarget);

    return removeNodeTwoChildren(at, nodeFather, nodeTarget);
}

static AVLTreeNode *removeNodeZeroChildren(
    AVLTree *at,
    AVLTreeNode **nodeFather,
    AVLTreeNode **nodeTarget)
{
    if (*nodeFather == NULL && *nodeTarget == at->root)
    {
        at->root = NULL;
        return *nodeTarget;
    }

    if ((*nodeFather)->left == *nodeTarget)
        (*nodeFather)->left = NULL;

    if ((*nodeFather)->right == *nodeTarget)
        (*nodeFather)->right = NULL;

    return *nodeTarget;
}

static AVLTreeNode *removeNodeOneChildren(
    AVLTree *at,
    AVLTreeNode **nodeFather,
    AVLTreeNode **nodeTarget)
{

    AVLTreeNode *child = (*nodeTarget)->left == NULL ? (*nodeTarget)->right : (*nodeTarget)->left;

    if (*nodeFather == NULL && *nodeTarget == at->root)
    {
        at->root = child;
        return *nodeTarget;
    }

    if ((*nodeFather)->left == *nodeTarget)
        (*nodeFather)->left = child;

    if ((*nodeFather)->right == *nodeTarget)
        (*nodeFather)->right = child;

    return *nodeTarget;
}

static AVLTreeNode *removeNodeTwoChildren(
    AVLTree *at,
    AVLTreeNode **nodeFather,
    AVLTreeNode **nodeTarget)
{
    AVLTreeNode *nodeLocalFather = *nodeTarget;
    AVLTreeNode *nodeLocalTarget = (*nodeTarget)->left;
    getMax(&nodeLocalFather, &nodeLocalTarget);
    AVLTreeNode *removedNode = verifyRemoveCondition(at,
                                                     &nodeLocalFather,
                                                     &nodeLocalTarget);
    removedNode->left = (*nodeTarget)->left;
    removedNode->right = (*nodeTarget)->right;

    if (*nodeFather == NULL && *nodeTarget == at->root)
    {
        at->root = removedNode;
        return *nodeTarget;
    }

    if ((*nodeFather)->left == *nodeTarget)
        (*nodeFather)->left = removedNode;

    if ((*nodeFather)->right == *nodeTarget)
        (*nodeFather)->right = removedNode;

    return *nodeTarget;
}

AVLTreeNode *removeAVLTree(AVLTree *at, void *target)
{
    if (isAVLTreeEmpty(*at))
        return NULL;

    AVLTreeNode *nodeFather = NULL;
    AVLTreeNode *nodeTarget = at->root;

    search(*at, target, &nodeFather, &nodeTarget);

    if (nodeTarget == NULL)
        return NULL;

    AVLTreeNode *removedNode = verifyRemoveCondition(at, &nodeFather, &nodeTarget);
    at->size--;
    return removedNode;
}*/
