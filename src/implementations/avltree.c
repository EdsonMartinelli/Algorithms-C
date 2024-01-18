#include <stdio.h>
#include "../headers/avltree.h"

static int maxHeight(AVLTreeNode *);
static AVLTreeNode *insertNode(AVLTree *, AVLTreeNode *, AVLTreeNode *);
static AVLTreeNode *leftRotation(AVLTreeNode *);
static AVLTreeNode *rightRotation(AVLTreeNode *);
static AVLTreeNode *search(AVLTree, void *, AVLTreeNode *);
static AVLTreeNode *getMin(AVLTreeNode *);
static AVLTreeNode *getMax(AVLTreeNode *);
static AVLTreeNode *removeNode(AVLTree *, AVLTreeNode *, void *);
static AVLTreeNode *verifyRemoveCondition(AVLTree *, AVLTreeNode *);
static AVLTreeNode *removeNodeZeroChildren(AVLTreeNode *);
static AVLTreeNode *removeNodeOneChildren(AVLTreeNode *);
static AVLTreeNode *removeNodeTwoChildren(AVLTree *, AVLTreeNode *);

void initAVLTree(AVLTree *bt, int (*comparator)(void *a, void *b))
{
    *bt = (AVLTree){.root = NULL, .size = 0, .comparator = comparator};
}

static int maxHeight(AVLTreeNode *target)
{
    if (target == NULL)
        return -1;
    return target->heightLeft <= target->heightRight ? target->heightRight : target->heightLeft;
}

static AVLTreeNode *leftRotation(AVLTreeNode *nodeTarget)
{
    if (nodeTarget == NULL)
        return NULL;

    AVLTreeNode *tempRight = nodeTarget->right;

    nodeTarget->right = (nodeTarget->right)->left;
    nodeTarget->heightRight = tempRight->heightLeft;

    tempRight->left = nodeTarget;
    tempRight->heightLeft = maxHeight(nodeTarget) + 1;

    return tempRight;
}

static AVLTreeNode *rightRotation(AVLTreeNode *nodeTarget)
{
    if (nodeTarget == NULL)
        return NULL;

    AVLTreeNode *tempLeft = nodeTarget->left;
    nodeTarget->left = (nodeTarget->left)->right;
    nodeTarget->heightLeft = tempLeft->heightRight;

    tempLeft->right = nodeTarget;
    tempLeft->heightRight = maxHeight(nodeTarget) + 1;

    return tempLeft;
}

static AVLTreeNode *insertNode(AVLTree *at, AVLTreeNode *current, AVLTreeNode *node)
{
    if (isAVLTreeEmpty(*at))
        return node;

    int comp = (*at->comparator)(current->content, node->content);

    if (comp > 0)
    {
        if (current->left != NULL)
        {
            AVLTreeNode *childNode = insertNode(at, current->left, node);
            current->left = childNode;
            current->heightLeft = maxHeight(current->left) + 1;
            int balanceFactor = current->heightLeft - current->heightRight;
            if (balanceFactor > 1)
            {
                if ((current->left)->heightLeft < (current->left)->heightRight)
                    current->left = leftRotation(current->left);
                return rightRotation(current);
            }
            return current;
        }
        current->heightLeft++;
        current->left = node;
        return current;
    }
    else
    {
        if (current->right != NULL)
        {
            AVLTreeNode *childNode = insertNode(at, current->right, node);
            current->right = childNode;
            current->heightRight = maxHeight(current->right) + 1;
            int balanceFactor = current->heightRight - current->heightLeft;
            if (balanceFactor > 1)
            {
                if ((current->right)->heightLeft > (current->right)->heightRight)
                    current->right = rightRotation(current->right);
                return leftRotation(current);
            }
            return current;
        }
        current->heightRight++;
        current->right = node;
        return current;
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

    AVLTreeNode *rootNode = insertNode(at, at->root, node);
    at->root = rootNode;
    at->size++;
    return rootNode;
}

bool isAVLTreeEmpty(AVLTree at)
{
    if (at.root == NULL && at.size == 0)
        return true;
    return false;
}

static AVLTreeNode *getMin(AVLTreeNode *current)
{
    if (current == NULL)
        return NULL;

    if (current->left == NULL)
        return current;
    return getMin(current->left);
}

AVLTreeNode *getMinAVLTree(AVLTree at)
{
    if (isAVLTreeEmpty(at))
        return NULL;

    return getMin(at.root);
}

static AVLTreeNode *getMax(AVLTreeNode *current)
{
    if (current == NULL)
        return NULL;

    if (current->right == NULL)
        return current;
    return getMax(current->right);
}

AVLTreeNode *getMaxAVLTree(AVLTree at)
{
    if (isAVLTreeEmpty(at))
        return NULL;

    return getMax(at.root);
}

static AVLTreeNode *search(
    AVLTree at,
    void *target,
    AVLTreeNode *current)
{
    if (current == NULL)
        return NULL;

    int comp = (*at.comparator)(current->content, target);

    if (comp == 0)
        return current;

    if (comp > 0)
        return search(at, target, current->left);
    else
        return search(at, target, current->right);
}

AVLTreeNode *searchAVLTree(AVLTree at, void *target)
{
    if (isAVLTreeEmpty(at))
        return NULL;

    return search(at, target, at.root);
}

static AVLTreeNode *verifyRemoveCondition(AVLTree *at, AVLTreeNode *target)
{
    if (target->left == NULL && target->right == NULL)
        return removeNodeZeroChildren(target);

    if (target->left == NULL || target->right == NULL)
        return removeNodeOneChildren(target);

    return removeNodeTwoChildren(at, target);
}

static AVLTreeNode *removeNodeZeroChildren(AVLTreeNode *target)
{
    return NULL;
}

static AVLTreeNode *removeNodeOneChildren(AVLTreeNode *target)
{
    if (target->left != NULL)
        return target->left;

    if (target->right != NULL)
        return target->right;
}

static AVLTreeNode *removeNodeTwoChildren(AVLTree *at, AVLTreeNode *target)
{
    AVLTreeNode *right = target->right;
    AVLTreeNode *max = getMax(target->left);
    AVLTreeNode *left = removeNode(at, target->left, max->content);

    max->left = left;
    max->right = right;
    max->heightLeft = maxHeight(left) + 1;
    max->heightRight = maxHeight(right) + 1;
    at->size++;
    return max;
}

static AVLTreeNode *removeNode(AVLTree *at, AVLTreeNode *current, void *target)
{
    if (current == NULL)
        return NULL;

    int comp = (*at->comparator)(current->content, target);

    if (comp == 0)
    {
        AVLTreeNode *subTreeRoot = verifyRemoveCondition(at, current);
        at->size--;
        return subTreeRoot;
    }

    if (comp > 0)
    {
        AVLTreeNode *childNode = removeNode(at, current->left, target);
        current->left = childNode;
        current->heightLeft = maxHeight(childNode) + 1;
        int balanceFactor = current->heightRight - current->heightLeft;
        if (balanceFactor > 1)
        {
            if ((current->right)->heightLeft > (current->right)->heightRight)
                current->left = rightRotation(current->left);
            return leftRotation(current);
        }
        return current;
    }
    else
    {
        AVLTreeNode *childNode = removeNode(at, current->right, target);
        current->right = childNode;
        current->heightRight = maxHeight(childNode) + 1;
        int balanceFactor = current->heightLeft - current->heightRight;
        if (balanceFactor > 1)
        {
            if ((current->left)->heightRight > (current->left)->heightLeft)
                current->right = leftRotation(current->right);
            return rightRotation(current);
        }
        return current;
    }
}

AVLTreeNode *removeAVLTree(AVLTree *at, void *target)
{
    if (isAVLTreeEmpty(*at))
        return NULL;

    AVLTreeNode *rootNode = removeNode(at, at->root, target);
    at->root = rootNode;
    return rootNode;
}
