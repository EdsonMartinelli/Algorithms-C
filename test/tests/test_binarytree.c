#include <stdlib.h>
#include "../Unity/unity.h"
#include "../../src/headers/binarytree.h"
#include "../../src/Utils/utils.h"

#define expSize 10

BinaryTree bt;

int comparator(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

void setUp()
{
    initBinaryTree(&bt, &comparator);
}

void tearDown() {}

void binaryTreeShouldBeInitializedCorrecty()
{
    TEST_ASSERT_EQUAL(0, bt.size);
    TEST_ASSERT_NULL(bt.root);
    TEST_ASSERT_NOT_NULL(bt.comparator);
}

void binaryTreeShouldInsertNodeCorrectyInRoot()
{
    int content = 2;
    BinaryTreeNode root = {.content = &content};
    BinaryTreeNode *temp = insertBinaryTree(&bt, &root);

    TEST_ASSERT_EQUAL(1, bt.size);
    TEST_ASSERT_EQUAL_PTR(&root, bt.root);
    TEST_ASSERT_EQUAL_PTR(temp, &root);
}

void binaryTreeShouldDoNothingIfInsertNodeIsNull()
{
    BinaryTreeNode *temp = insertBinaryTree(&bt, NULL);
    TEST_ASSERT_EQUAL(0, bt.size);
    TEST_ASSERT_NULL(bt.root);
    TEST_ASSERT_NULL(temp);
}

void binaryTreeShouldDoNothingIfBinaryTreeIsNull()
{
    int content = 2;
    BinaryTreeNode root = {.content = &content};
    BinaryTreeNode *temp = insertBinaryTree(NULL, &root);
    TEST_ASSERT_EQUAL(0, bt.size);
    TEST_ASSERT_NULL(bt.root);
    TEST_ASSERT_NULL(temp);
}

void binaryTreeShouldReturnCorrectyWhenItIsEmptyOrNot()
{
    TEST_ASSERT_TRUE(isBinaryTreeEmpty(bt));
    TEST_ASSERT_EQUAL(0, bt.size);

    int content = 2;
    BinaryTreeNode root = {.content = &content};
    BinaryTreeNode *temp = insertBinaryTree(&bt, &root);

    TEST_ASSERT_FALSE(isBinaryTreeEmpty(bt));
    TEST_ASSERT_EQUAL(1, bt.size);
}

void testPrintBinaryTree()
{
    int size = 5;
    int content[] = {3, 5, 6, 1, 2};
    BinaryTreeNode items[size];
    for (int i = 0; i < size; i++)
        items[i] = (BinaryTreeNode){.content = content + i};

    for (int i = 0; i < size; i++)
        insertBinaryTree(&bt, items + i);

    printBinaryTree(bt);
}
int main()
{
    UNITY_BEGIN();
    RUN_TEST(binaryTreeShouldBeInitializedCorrecty);
    RUN_TEST(binaryTreeShouldInsertNodeCorrectyInRoot);
    RUN_TEST(binaryTreeShouldDoNothingIfInsertNodeIsNull);
    RUN_TEST(binaryTreeShouldDoNothingIfBinaryTreeIsNull);
    RUN_TEST(binaryTreeShouldReturnCorrectyWhenItIsEmptyOrNot);
    RUN_TEST(testPrintBinaryTree);
    return UNITY_END();
}