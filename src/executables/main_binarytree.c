#include <stdio.h>
#include "../headers/binarytree.h"

#define expSize 10

int comparator(void *a, void *b)
{
    return *(int *)a - *(int *)b;
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

int main()
{
    BinaryTree bt;
    initBinaryTree(&bt, &comparator);
    int values[] = {10, 20, 5, 4, 8, 12, 22, 40, 1, 2};
    BinaryTreeNode items[expSize];
    for (int i = 0; i < expSize; i++)
        items[i] = (BinaryTreeNode){.content = values + i};

    for (int i = 0; i < expSize; i++)
        insertBinaryTree(&bt, items + i);

    removeBinaryTree(&bt, values + expSize - 1);
    removeBinaryTree(&bt, values + 2);
    removeBinaryTree(&bt, values + 6);
    removeBinaryTree(&bt, values);

    printBinaryTree(bt);

    return 0;
}