#include <stdio.h>
#include "../headers/binarytree.h"

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

BinaryTreeNode *getMinBinaryTree(BinaryTree bt)
{
    if (isBinaryTreeEmpty(bt))
        return NULL;

    BinaryTreeNode *temp = bt.root;
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}

BinaryTreeNode *getMaxBinaryTree(BinaryTree bt)
{
    if (isBinaryTreeEmpty(bt))
        return NULL;

    BinaryTreeNode *temp = bt.root;
    while (temp->right != NULL)
        temp = temp->right;
    return temp;
}

BinaryTreeNode *searchBinaryTree(BinaryTree bt, void *target)
{
    if (isBinaryTreeEmpty(bt))
        return NULL;

    BinaryTreeNode *temp = bt.root;
    while (temp != NULL)
    {
        int comp = (*bt.comparator)(temp->content, target);

        if (comp == 0)
            return temp;

        if (comp > 0)
            temp = temp->left;
        else
            temp = temp->right;
    }

    return NULL;
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
