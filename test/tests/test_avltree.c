#include <stdlib.h>
#include "../Unity/unity.h"
#include "../../src/headers/avltree.h"
#include "../../src/Utils/utils.h"

#define expSize 10

AVLTree at;

int comparator(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

void setUp()
{
    initAVLTree(&at, &comparator);
}

void tearDown() {}

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
    printf("\n\n");
}

static bool verifyTreeCorrectness(AVLTree avltree, AVLTreeNode *node)
{
    if (node == NULL)
        return true;

    bool isLeftCorrect = true;
    bool isRightCorrect = true;

    int balanceFactor = node->heightLeft - node->heightRight;
    if (balanceFactor < -1 || balanceFactor > 1)
        return false;

    if (node->left != NULL)
        isLeftCorrect = (*avltree.comparator)(node->content, (node->left)->content) >= 0 ? true : false;

    if (node->right != NULL)
        isRightCorrect = (*avltree.comparator)(node->content, (node->right)->content) <= 0 ? true : false;

    if (isRightCorrect && isLeftCorrect)
    {
        bool isLeftTreeCorrect = verifyTreeCorrectness(avltree, node->left);
        bool isRightTreeCorrect = verifyTreeCorrectness(avltree, node->right);
        return isLeftTreeCorrect && isRightTreeCorrect;
    }
    else
    {
        return false;
    }
}

static bool verifyBalanceFactorCorrectness(AVLTree avltree, AVLTreeNode *node, int *height)
{
    if (node == NULL)
        return true;

    int heightLeft = 0;
    int heightRight = 0;
    bool isLeftHeightCorrect = verifyBalanceFactorCorrectness(avltree, node->left, &heightLeft);
    bool isRightHeightCorrect = verifyBalanceFactorCorrectness(avltree, node->right, &heightRight);
    if (height != NULL)
        *height = heightLeft <= heightRight ? heightRight + 1 : heightLeft + 1;

    if (isLeftHeightCorrect && isRightHeightCorrect)
    {
        int bf = node->heightLeft - node->heightRight;
        if (node->heightLeft == heightLeft &&
            node->heightRight == heightRight &&
            bf >= -1 && bf <= 1)
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}

void avlTreeShouldBeInitializedCorrecty()
{
    TEST_ASSERT_EQUAL(0, at.size);
    TEST_ASSERT_NULL(at.root);
    TEST_ASSERT_NOT_NULL(at.comparator);
}

void avlTreeShouldUseRightRotationCorrecty()
{
    int content[expSize];
    AVLTreeNode items[expSize];

    for (int i = 0; i < expSize; i++)
        content[i] = i;

    for (int i = 0; i < expSize; i++)
        items[i] = (AVLTreeNode){.content = content + i};

    for (int i = 0; i < expSize; i++)
    {
        AVLTreeNode *temp = insertAVLTree(&at, items + i);
        TEST_ASSERT_NOT_NULL(temp);
        TEST_ASSERT_EQUAL_PTR(items + i, temp);
    }

    TEST_ASSERT_EQUAL(expSize, at.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(at, at.root));
    TEST_ASSERT_TRUE(verifyBalanceFactorCorrectness(at, at.root, NULL));
}

void avlTreeShouldUseLeftRotationCorrecty()
{
    int content[expSize];
    AVLTreeNode items[expSize];

    for (int i = 0; i < expSize; i++)
        content[i] = expSize - 1 - i;

    for (int i = 0; i < expSize; i++)
        items[i] = (AVLTreeNode){.content = content + i};

    for (int i = 0; i < expSize; i++)
    {
        AVLTreeNode *temp = insertAVLTree(&at, items + i);
        TEST_ASSERT_NOT_NULL(temp);
        TEST_ASSERT_EQUAL_PTR(items + i, temp);
    }
    TEST_ASSERT_EQUAL(expSize, at.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(at, at.root));
    TEST_ASSERT_TRUE(verifyBalanceFactorCorrectness(at, at.root, NULL));
}

void avlTreeShouldUseLeftRightRotationCorrecty()
{
    int content[expSize];
    AVLTreeNode items[expSize];

    for (int i = 0; i < expSize; i++)
        content[i] = i % 2 == 0 ? expSize - 1 - (i / 2) : i / 2;

    for (int i = 0; i < expSize; i++)
        items[i] = (AVLTreeNode){.content = content + i};

    for (int i = 0; i < expSize; i++)
    {
        AVLTreeNode *temp = insertAVLTree(&at, items + i);
        TEST_ASSERT_NOT_NULL(temp);
        TEST_ASSERT_EQUAL_PTR(items + i, temp);
    }

    TEST_ASSERT_EQUAL(expSize, at.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(at, at.root));
    TEST_ASSERT_TRUE(verifyBalanceFactorCorrectness(at, at.root, NULL));
}

void avlTreeShouldUseRightLeftRotationCorrecty()
{
    int content[expSize];
    AVLTreeNode items[expSize];

    for (int i = 0; i < expSize; i++)
        content[i] = i % 2 == 0 ? i / 2 : expSize - 1 - (i / 2);

    for (int i = 0; i < expSize; i++)
        items[i] = (AVLTreeNode){.content = content + i};

    for (int i = 0; i < expSize; i++)
    {
        AVLTreeNode *temp = insertAVLTree(&at, items + i);
        TEST_ASSERT_NOT_NULL(temp);
        TEST_ASSERT_EQUAL_PTR(items + i, temp);
    }

    TEST_ASSERT_EQUAL(expSize, at.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(at, at.root));
    TEST_ASSERT_TRUE(verifyBalanceFactorCorrectness(at, at.root, NULL));
}

void avlTreeShouldInsertNodeCorrectyWithRandom()
{
    int content[expSize];
    AVLTreeNode items[expSize];

    for (int i = 0; i < expSize; i++)
        content[i] = randomIntNumber(-100, 100, i);

    for (int i = 0; i < expSize; i++)
        items[i] = (AVLTreeNode){.content = content + i};

    for (int i = 0; i < expSize; i++)
    {
        AVLTreeNode *temp = insertAVLTree(&at, items + i);
        TEST_ASSERT_NOT_NULL(temp);
        TEST_ASSERT_EQUAL_PTR(items + i, temp);
    }

    TEST_ASSERT_EQUAL(expSize, at.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(at, at.root));
    TEST_ASSERT_TRUE(verifyBalanceFactorCorrectness(at, at.root, NULL));
}

void avlTreeShouldInsertNodeCorrecty()
{
    // int content[] = {-57, 37, -51, -41, -11, 38, -78, -34, -41, 82};
    int content[] = {43, 137, 49, 59, 89, 138, 22, 66, 59, 182};
    AVLTreeNode items[expSize];

    for (int i = 0; i < expSize; i++)
        items[i] = (AVLTreeNode){.content = content + i};

    for (int i = 0; i < expSize; i++)
    {
        AVLTreeNode *temp = insertAVLTree(&at, items + i);
        TEST_ASSERT_NOT_NULL(temp);
        TEST_ASSERT_EQUAL_PTR(items + i, temp);
    }
    TEST_ASSERT_EQUAL(expSize, at.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(at, at.root));
    TEST_ASSERT_TRUE(verifyBalanceFactorCorrectness(at, at.root, NULL));
}

void avlTreeShouldDoNothingIfInsertNodeIsNull()
{
    AVLTreeNode *temp = insertAVLTree(&at, NULL);
    TEST_ASSERT_EQUAL(0, at.size);
    TEST_ASSERT_NULL(at.root);
    TEST_ASSERT_NULL(temp);
}

void avlTreeShouldDoNothingIfBinaryTreeIsNull()
{
    int content = 2;
    AVLTreeNode root = {.content = &content};
    AVLTreeNode *temp = insertAVLTree(NULL, &root);
    TEST_ASSERT_EQUAL(0, at.size);
    TEST_ASSERT_NULL(at.root);
    TEST_ASSERT_NULL(temp);
}

void avlTreeShouldReturnCorrectyWhenItIsEmptyOrNot()
{
    TEST_ASSERT_TRUE(isAVLTreeEmpty(at));
    TEST_ASSERT_EQUAL(0, at.size);

    int content = 2;
    AVLTreeNode root = {.content = &content};
    AVLTreeNode *temp = insertAVLTree(&at, &root);

    TEST_ASSERT_FALSE(isAVLTreeEmpty(at));
    TEST_ASSERT_EQUAL(1, at.size);
}

void avlTreeShouldGetMinNodeCorrecty()
{
    AVLTreeNode *tempNull = getMinAVLTree(at);
    TEST_ASSERT_NULL(tempNull);

    int content[expSize];
    AVLTreeNode items[expSize];

    for (int i = 0; i < expSize - 1; i++)
        content[i] = randomIntNumber(1, 100, i);
    content[expSize - 1] = 0;

    for (int i = 0; i < expSize; i++)
        items[i] = (AVLTreeNode){.content = content + i};

    for (int i = 0; i < expSize; i++)
    {
        AVLTreeNode *temp = insertAVLTree(&at, items + i);
        TEST_ASSERT_NOT_NULL(temp);
        TEST_ASSERT_EQUAL_PTR(items + i, temp);
    }

    TEST_ASSERT_EQUAL(expSize, at.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(at, at.root));
    TEST_ASSERT_TRUE(verifyBalanceFactorCorrectness(at, at.root, NULL));

    AVLTreeNode *temp = getMinAVLTree(at);
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_EQUAL(0, *(int *)temp->content);
}

void avlTreeShouldGetMaxNodeCorrecty()
{
    AVLTreeNode *tempNull = getMaxAVLTree(at);
    TEST_ASSERT_NULL(tempNull);

    int content[expSize];
    AVLTreeNode items[expSize];

    for (int i = 0; i < expSize - 1; i++)
        content[i] = randomIntNumber(0, 100, i);
    content[expSize - 1] = 101;

    for (int i = 0; i < expSize; i++)
        items[i] = (AVLTreeNode){.content = content + i};

    for (int i = 0; i < expSize; i++)
    {
        AVLTreeNode *temp = insertAVLTree(&at, items + i);
        TEST_ASSERT_NOT_NULL(temp);
        TEST_ASSERT_EQUAL_PTR(items + i, temp);
    }

    TEST_ASSERT_EQUAL(expSize, at.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(at, at.root));
    TEST_ASSERT_TRUE(verifyBalanceFactorCorrectness(at, at.root, NULL));

    AVLTreeNode *temp = getMaxAVLTree(at);
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_EQUAL(101, *(int *)temp->content);
}

/*void binaryTreeShouldSearchNodeCorrecty()
{
    int searchNumber = 101;
    AVLTreeNode *tempNull = searchBinaryTree(at, &searchNumber);
    TEST_ASSERT_NULL(tempNull);

    int content[expSize];
    AVLTreeNode items[expSize];

    for (int i = 0; i < expSize; i++)
        content[i] = i % 2 > 0 ? randomIntNumber(-200, 100, i) : randomIntNumber(102, 200, i);

    int index = randomIntNumber(0, expSize, 0);
    content[index] = searchNumber;

    for (int i = 0; i < expSize; i++)
        items[i] = (AVLTreeNode){.content = content + i};

    for (int i = 0; i < expSize; i++)
    {
        AVLTreeNode *temp = insertBinaryTree(&at, items + i);
        TEST_ASSERT_NOT_NULL(temp);
        TEST_ASSERT_EQUAL_PTR(items + i, temp);
    }

    TEST_ASSERT_EQUAL(expSize, at.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(at, at.root));

    AVLTreeNode *temp = searchBinaryTree(at, &searchNumber);
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_EQUAL_PTR(items + index, temp);
    TEST_ASSERT_EQUAL(101, *(int *)temp->content);

    int wrongTarget = 1000;
    temp = searchBinaryTree(at, &wrongTarget);
    TEST_ASSERT_NULL(temp);
}

void binaryTreeShouldRemoveNodeCorrectyWithRandomNodes()
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

    BinaryTreeNode *temp = removeBinaryTree(&bt, &searchNumber);
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_EQUAL_PTR(items + index, temp);
    TEST_ASSERT_EQUAL(101, *(int *)temp->content);

    TEST_ASSERT_EQUAL(expSize - 1, bt.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(bt, bt.root));

    int wrongTarget = 1000;
    temp = removeBinaryTree(&bt, &wrongTarget);
    TEST_ASSERT_NULL(temp);
}

void binaryTreeShouldRemoveNodeCorrecty()
{
    int values[] = {10, 20, 5, 4, 8, 12, 22, 40, 1, 2};
    BinaryTreeNode items[expSize];
    for (int i = 0; i < expSize; i++)
        items[i] = (BinaryTreeNode){.content = values + i};

    for (int i = 0; i < expSize; i++)
    {
        BinaryTreeNode *temp = insertBinaryTree(&bt, items + i);
        TEST_ASSERT_NOT_NULL(temp);
        TEST_ASSERT_EQUAL_PTR(items + i, temp);
    }

    // Leaf (2)
    BinaryTreeNode *temp = removeBinaryTree(&bt, values + expSize - 1);
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_EQUAL_PTR(items + expSize - 1, temp);
    TEST_ASSERT_EQUAL(values[expSize - 1], *(int *)temp->content);
    TEST_ASSERT_EQUAL(expSize - 1, bt.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(bt, bt.root));

    // Branch With 2 childrens (5)
    temp = removeBinaryTree(&bt, values + 2);
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_EQUAL_PTR(items + 2, temp);
    TEST_ASSERT_EQUAL(values[2], *(int *)temp->content);
    TEST_ASSERT_EQUAL(expSize - 2, bt.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(bt, bt.root));

    // Branch With 1 childrens (22)
    temp = removeBinaryTree(&bt, values + 6);
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_EQUAL_PTR(items + 6, temp);
    TEST_ASSERT_EQUAL(values[6], *(int *)temp->content);
    TEST_ASSERT_EQUAL(expSize - 3, bt.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(bt, bt.root));

    // Root (10)
    temp = removeBinaryTree(&bt, values);
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_EQUAL_PTR(items, temp);
    TEST_ASSERT_EQUAL(values[0], *(int *)temp->content);
    TEST_ASSERT_EQUAL(expSize - 4, bt.size);
    TEST_ASSERT_TRUE(verifyTreeCorrectness(bt, bt.root));
}
*/

int main()
{
    UNITY_BEGIN();
    RUN_TEST(avlTreeShouldBeInitializedCorrecty);
    RUN_TEST(avlTreeShouldUseRightRotationCorrecty);
    RUN_TEST(avlTreeShouldUseLeftRotationCorrecty);
    RUN_TEST(avlTreeShouldUseLeftRightRotationCorrecty);
    RUN_TEST(avlTreeShouldUseRightLeftRotationCorrecty);
    RUN_TEST(avlTreeShouldInsertNodeCorrectyWithRandom);
    RUN_TEST(avlTreeShouldInsertNodeCorrecty);
    RUN_TEST(avlTreeShouldDoNothingIfInsertNodeIsNull);
    RUN_TEST(avlTreeShouldDoNothingIfBinaryTreeIsNull);
    RUN_TEST(avlTreeShouldReturnCorrectyWhenItIsEmptyOrNot);
    RUN_TEST(avlTreeShouldGetMinNodeCorrecty);
    RUN_TEST(avlTreeShouldGetMaxNodeCorrecty);
    /* RUN_TEST(binaryTreeShouldSearchNodeCorrecty);
     RUN_TEST(binaryTreeShouldRemoveNodeCorrectyWithRandomNodes);
     RUN_TEST(binaryTreeShouldRemoveNodeCorrecty);*/
    return UNITY_END();
}