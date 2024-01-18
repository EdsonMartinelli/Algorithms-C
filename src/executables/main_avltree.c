#include <stdio.h>
#include "../headers/avltree.h"

#define expSize 10

int comparator(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

static void printAVLTreeNode(AVLTreeNode *node, int level, int father)
{
    if (node == NULL)
        return;
    printf("Level[%i]: %i(%i) ", level, *(int *)node->content, father);
    printAVLTreeNode(node->left, level + 1, *(int *)node->content);
    printAVLTreeNode(node->right, level + 1, *(int *)node->content);
}

void printAVLTree(AVLTree att)
{
    printAVLTreeNode(att.root, 0, -1);
    printf("\n");
}

int main()
{
    AVLTree at;
    initAVLTree(&at, &comparator);
    int values[] = {10, 20, 5, 4, 8, 12, 22, 40, 1, 2};
    AVLTreeNode items[expSize];
    for (int i = 0; i < expSize; i++)
        items[i] = (AVLTreeNode){.content = values + i};

    for (int i = 0; i < expSize; i++)
        insertAVLTree(&at, items + i);

    removeAVLTree(&at, values + expSize - 1);
    removeAVLTree(&at, values + 2);
    removeAVLTree(&at, values + 6);
    removeAVLTree(&at, values);

    printAVLTree(at);

    return 0;
}