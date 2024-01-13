#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <stdbool.h>

typedef struct Node
{
    void *content;
    struct Node *left;
    struct Node *right;
} BinaryTreeNode;

typedef struct
{
    BinaryTreeNode *root;
    int (*comparator)(void *, void *);
    int size;
} BinaryTree;

void initBinaryTree(BinaryTree *, int (*comparator)(void *, void *));
BinaryTreeNode *insertBinaryTree(BinaryTree *, BinaryTreeNode *);
bool isBinaryTreeEmpty(BinaryTree);
BinaryTreeNode *getMinBinaryTree(BinaryTree);
BinaryTreeNode *getMaxBinaryTree(BinaryTree);
BinaryTreeNode *searchBinaryTree(BinaryTree, void *);

void printBinaryTree(BinaryTree);

#endif