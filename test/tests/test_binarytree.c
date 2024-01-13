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

static bool verifyTreeCorrectness(BinaryTree bintree, BinaryTreeNode *node)
{
    if (node == NULL)
        return true;

    bool isLeftCorrect = true;
    bool isRightCorrect = true;

    if (node->left != NULL)
        isLeftCorrect = (*bintree.comparator)(node->content, (node->left)->content) > 0 ? true : false;

    if (node->right != NULL)
        isRightCorrect = (*bintree.comparator)(node->content, (node->right)->content) <= 0 ? true : false;

    if (isRightCorrect && isLeftCorrect)
    {
        bool isLeftTreeCorrect = verifyTreeCorrectness(bintree, node->left);
        bool isRightTreeCorrect = verifyTreeCorrectness(bintree, node->right);
        return isLeftTreeCorrect && isRightTreeCorrect;
    }
    else
    {
        return false;
    }
}

void binaryTreeShouldBeInitializedCorrecty()
{
    TEST_ASSERT_EQUAL(0, bt.size);
    TEST_ASSERT_NULL(bt.root);
    TEST_ASSERT_NOT_NULL(bt.comparator);
}

void binaryTreeShouldInsertNodeCorrecty()
{
    int content[expSize];
    BinaryTreeNode items[expSize];

    for (int i = 0; i < expSize; i++)
        content[i] = randomIntNumber(-100, 100, i);

    for (int i = 0; i < expSize; i++)
        items[i] = (BinaryTreeNode){.content = content + i};

    for (int i = 0; i < expSize; i++)
    {
        BinaryTreeNode *temp = insertBinaryTree(&bt, items + i);
        TEST_ASSERT_NOT_NULL(temp);
        TEST_ASSERT_EQUAL_PTR(items + i, temp);
    }

    TEST_ASSERT_EQUAL(expSize, bt.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(bt, bt.root));
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

void binaryTreeShouldGetMinNodeCorrecty()
{
    BinaryTreeNode *tempNull = getMinBinaryTree(bt);
    TEST_ASSERT_NULL(tempNull);

    int content[expSize];
    BinaryTreeNode items[expSize];

    for (int i = 0; i < expSize - 1; i++)
        content[i] = randomIntNumber(1, 100, i);
    content[expSize - 1] = 0;

    for (int i = 0; i < expSize; i++)
        items[i] = (BinaryTreeNode){.content = content + i};

    for (int i = 0; i < expSize; i++)
    {
        BinaryTreeNode *temp = insertBinaryTree(&bt, items + i);
        TEST_ASSERT_NOT_NULL(temp);
        TEST_ASSERT_EQUAL_PTR(items + i, temp);
    }

    TEST_ASSERT_EQUAL(expSize, bt.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(bt, bt.root));

    BinaryTreeNode *temp = getMinBinaryTree(bt);
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_EQUAL(0, *(int *)temp->content);
}

void binaryTreeShouldGetMaxNodeCorrecty()
{
    BinaryTreeNode *tempNull = getMaxBinaryTree(bt);
    TEST_ASSERT_NULL(tempNull);

    int content[expSize];
    BinaryTreeNode items[expSize];

    for (int i = 0; i < expSize - 1; i++)
        content[i] = randomIntNumber(0, 100, i);
    content[expSize - 1] = 101;

    for (int i = 0; i < expSize; i++)
        items[i] = (BinaryTreeNode){.content = content + i};

    for (int i = 0; i < expSize; i++)
    {
        BinaryTreeNode *temp = insertBinaryTree(&bt, items + i);
        TEST_ASSERT_NOT_NULL(temp);
        TEST_ASSERT_EQUAL_PTR(items + i, temp);
    }

    TEST_ASSERT_EQUAL(expSize, bt.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(bt, bt.root));

    BinaryTreeNode *temp = getMaxBinaryTree(bt);
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_EQUAL(101, *(int *)temp->content);
}

void binaryTreeShouldSearchNodeCorrecty()
{
    int searchNumber = 101;
    BinaryTreeNode *tempNull = searchBinaryTree(bt, &searchNumber);
    TEST_ASSERT_NULL(tempNull);

    int content[expSize];
    BinaryTreeNode items[expSize];

    for (int i = 0; i < expSize; i++)
        content[i] = i % 2 > 0 ? randomIntNumber(-200, 100, i) : randomIntNumber(102, 200, i);

    int index = randomIntNumber(0, expSize, 0);
    content[index] = searchNumber;

    for (int i = 0; i < expSize; i++)
        items[i] = (BinaryTreeNode){.content = content + i};

    for (int i = 0; i < expSize; i++)
    {
        BinaryTreeNode *temp = insertBinaryTree(&bt, items + i);
        TEST_ASSERT_NOT_NULL(temp);
        TEST_ASSERT_EQUAL_PTR(items + i, temp);
    }

    TEST_ASSERT_EQUAL(expSize, bt.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(bt, bt.root));

    BinaryTreeNode *temp = searchBinaryTree(bt, &searchNumber);
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_EQUAL_PTR(items + index, temp);
    TEST_ASSERT_EQUAL(101, *(int *)temp->content);

    int wrongTarget = 1000;
    temp = searchBinaryTree(bt, &wrongTarget);
    TEST_ASSERT_NULL(temp);
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
    RUN_TEST(binaryTreeShouldInsertNodeCorrecty);
    RUN_TEST(binaryTreeShouldDoNothingIfInsertNodeIsNull);
    RUN_TEST(binaryTreeShouldDoNothingIfBinaryTreeIsNull);
    RUN_TEST(binaryTreeShouldReturnCorrectyWhenItIsEmptyOrNot);
    RUN_TEST(binaryTreeShouldGetMinNodeCorrecty);
    RUN_TEST(binaryTreeShouldGetMaxNodeCorrecty);
    RUN_TEST(binaryTreeShouldSearchNodeCorrecty);
    // RUN_TEST(testPrintBinaryTree);
    return UNITY_END();
}