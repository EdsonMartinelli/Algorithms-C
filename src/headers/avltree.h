#ifndef AVLTREE_H
#define AVLTREE_H
#include <stdbool.h>

typedef struct Node
{
    void *content;
    int heightLeft;
    struct Node *left;
    int heightRight;
    struct Node *right;
} AVLTreeNode;

typedef struct
{
    AVLTreeNode *root;
    int (*comparator)(void *, void *);
    int size;
} AVLTree;

void initAVLTree(AVLTree *, int (*comparator)(void *, void *));
AVLTreeNode *insertAVLTree(AVLTree *, AVLTreeNode *);
bool isAVLTreeEmpty(AVLTree);
AVLTreeNode *getMinAVLTree(AVLTree);
AVLTreeNode *getMaxAVLTree(AVLTree);
AVLTreeNode *searchAVLTree(AVLTree, void *);
AVLTreeNode *removeAVLTree(AVLTree *, void *);

#endif