#include <stdlib.h>
#include "../../Unity/unity.h"
#include "../../../src/Vector/implementation/vector.h"

Vector vec;
int expSize = 6;
int a = 1;
int b = 2;
int c = 10;

void setUp()
{
    initVector(&vec);
}

void tearDown()
{
    freeVector(&vec);
}

static void initializeWithElements()
{
    for (int i = 0; i < expSize; i++)
        if (i % 2 == 0)
            pushBackVector(&vec, &a);
        else
            pushBackVector(&vec, &b);
}

static void initializeWithTheSameElement()
{
    for (int i = 0; i < expSize; i++)
        pushBackVector(&vec, &a);
}

void vectorShouldBeInitialized()
{
    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(0, vec.size);
    TEST_ASSERT_NOT_NULL(vec.array);
    TEST_ASSERT_EMPTY(vec.array);
}

void vectorShouldPushBackElement()
{

    initializeWithElements();

    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(expSize, vec.size);

    for (int i = 0; i < vec.size; i++)
    {
        if (i % 2 == 0)
        {
            if ((*(int *)(vec.array[i])) != a)
                TEST_FAIL();
        }
        else
        {
            if ((*(int *)(vec.array[i])) != b)
                TEST_FAIL();
        }
    }
}

void vectorShouldPopBackElement()
{
    initializeWithElements();

    void *bPop = popBackVector(&vec);
    void *aPop = popBackVector(&vec);

    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(expSize - 2, vec.size);

    for (int i = 0; i < vec.size; i++)
    {
        if (i % 2 == 0)
        {
            if ((*(int *)(vec.array[i])) != a)
                TEST_FAIL();
        }
        else
        {
            if ((*(int *)(vec.array[i])) != b)
                TEST_FAIL();
        }
    }

    TEST_ASSERT_EQUAL_PTR(bPop, &b);
    TEST_ASSERT_EQUAL_PTR(aPop, &a);
}

void vectorShouldInsertElement()
{
    int index = 1;
    initializeWithElements();

    insertVector(&vec, &c, index);

    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(expSize + 1, vec.size);

    if ((*(int *)(vec.array[index])) != c)
        TEST_FAIL();

    for (int i = 0; i < index; i++)
    {
        if (i % 2 == 0)
        {
            if ((*(int *)(vec.array[i])) != a)
                TEST_FAIL();
        }
        else
        {
            if ((*(int *)(vec.array[i])) != b)
                TEST_FAIL();
        }
    }

    for (int i = index + 1; i < vec.size; i++)
    {
        if (i % 2 == 1)
        {
            if ((*(int *)(vec.array[i])) != a)
                TEST_FAIL();
        }
        else
        {
            if ((*(int *)(vec.array[i])) != b)
                TEST_FAIL();
        }
    }
}

void vectorShouldInsertElementInTheBegin()
{
    int index = 0;
    initializeWithElements();

    insertVector(&vec, &c, index);

    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(expSize + 1, vec.size);

    if ((*(int *)(vec.array[index])) != c)
        TEST_FAIL();

    for (int i = index + 1; i < index; i++)
    {
        if (i % 2 == 1)
        {
            if ((*(int *)(vec.array[i])) != a)
                TEST_FAIL();
        }
        else
        {
            if ((*(int *)(vec.array[i])) != b)
                TEST_FAIL();
        }
    }
}

void vectorShouldInsertElementInTheEnd()
{
    int index = expSize;
    initializeWithElements();

    insertVector(&vec, &c, index);

    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(expSize + 1, vec.size);

    if ((*(int *)(vec.array[index])) != c)
        TEST_FAIL();

    for (int i = 0; i < expSize; i++)
    {
        if (i % 2 == 0)
        {
            if ((*(int *)(vec.array[i])) != a)
                TEST_FAIL();
        }
        else
        {
            if ((*(int *)(vec.array[i])) != b)
                TEST_FAIL();
        }
    }
}

void vectorShouldInsertNElements()
{
    int index = 1;
    int n = 2;
    initializeWithTheSameElement();

    insertNVector(&vec, &c, n, index);

    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(expSize + n, vec.size);

    for (int i = 0; i < index; i++)
        if ((*(int *)(vec.array[i])) != a)
            TEST_FAIL();

    for (int i = index; i < index + n; i++)
        if ((*(int *)(vec.array[index])) != c)
            TEST_FAIL();

    for (int i = index + n; i < vec.size; i++)
        if ((*(int *)(vec.array[i])) != a)
            TEST_FAIL();
}

void vectorShouldInsertNElementsInTheBegin()
{
    int index = 0;
    int n = 3;
    initializeWithTheSameElement();

    insertNVector(&vec, &c, n, index);

    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(expSize + n, vec.size);

    for (int i = 0; i < n; i++)
        if ((*(int *)(vec.array[index])) != c)
            TEST_FAIL();

    for (int i = index + n; i < vec.size; i++)
        if ((*(int *)(vec.array[i])) != a)
            TEST_FAIL();
}

void vectorShouldInsertNElementsInTheEnd()
{
    int index = expSize;
    int n = 3;
    initializeWithTheSameElement();

    insertNVector(&vec, &c, n, index);

    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(expSize + n, vec.size);

    for (int i = 0; i < expSize; i++)
        if ((*(int *)(vec.array[i])) != a)
            TEST_FAIL();

    for (int i = expSize; i < expSize + n; i++)
        if ((*(int *)(vec.array[index])) != c)
            TEST_FAIL();
}

void vectorShouldInsertArray()
{
    void **array = (void **)malloc(sizeof(void *) * 5);
    array[0] = &c;
    array[1] = &c;
    array[2] = &c;
    array[3] = &c;
    array[4] = &c;
    int index = 1;
    int firstIndex = 0;
    int lastIndex = 2;
    int n = lastIndex - firstIndex;
    initializeWithTheSameElement();

    insertArrayVector(&vec, array, firstIndex, lastIndex, index);

    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(expSize + n, vec.size);

    for (int i = 0; i < index; i++)
        if ((*(int *)(vec.array[i])) != a)
            TEST_FAIL();

    for (int i = index; i < index + n; i++)
        if ((*(int *)(vec.array[index])) != c)
            TEST_FAIL();

    for (int i = index + n; i < vec.size; i++)
        if ((*(int *)(vec.array[i])) != a)
            TEST_FAIL();

    free(array);
}

void vectorShouldInsertArrayInTheBegin()
{
    void **array = (void **)malloc(sizeof(void *) * 5);
    array[0] = &c;
    array[1] = &c;
    array[2] = &c;
    array[3] = &c;
    array[4] = &c;
    int index = 0;
    int firstIndex = 0;
    int lastIndex = 2;
    int n = lastIndex - firstIndex;
    initializeWithTheSameElement();

    insertArrayVector(&vec, array, firstIndex, lastIndex, index);

    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(expSize + n, vec.size);

    for (int i = 0; i < n; i++)
        if ((*(int *)(vec.array[index])) != c)
            TEST_FAIL();

    for (int i = index + n; i < vec.size; i++)
        if ((*(int *)(vec.array[i])) != a)
            TEST_FAIL();

    free(array);
}

void vectorShouldInsertArrayInTheEnd()
{
    void **array = (void **)malloc(sizeof(void *) * 5);
    array[0] = &c;
    array[1] = &c;
    array[2] = &c;
    array[3] = &c;
    array[4] = &c;
    int index = expSize;
    int firstIndex = 0;
    int lastIndex = 2;
    int n = lastIndex - firstIndex;
    initializeWithTheSameElement();

    insertArrayVector(&vec, array, firstIndex, lastIndex, index);

    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(expSize + n, vec.size);

    for (int i = 0; i < expSize; i++)
        if ((*(int *)(vec.array[i])) != a)
            TEST_FAIL();

    for (int i = expSize; i < expSize + n; i++)
        if ((*(int *)(vec.array[index])) != c)
            TEST_FAIL();

    free(array);
}

void vectorShouldEraseElements()
{
    int firstIndex = 2;
    int lastIndex = 4;
    int n = lastIndex - firstIndex;
    initializeWithElements();

    eraseVector(&vec, firstIndex, lastIndex);

    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(expSize - n, vec.size);

    for (int i = 0; i < vec.size; i++)
    {
        if (i % 2 == 0)
        {
            if ((*(int *)(vec.array[i])) != a)
                TEST_FAIL();
        }
        else
        {
            if ((*(int *)(vec.array[i])) != b)
                TEST_FAIL();
        }
    }
}

void vectorShouldEraseAllElements()
{
    int firstIndex = 0;
    int lastIndex = expSize;
    int n = lastIndex - firstIndex;
    initializeWithElements();

    eraseVector(&vec, firstIndex, lastIndex);

    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(0, vec.size);
}

void vectorsShouldSwap()
{
    initializeWithElements();
    void **p1 = vec.array;
    Vector vec2;
    initVector(&vec2);
    void **p2 = vec2.array;
    swapVector(&vec, &vec2);

    TEST_ASSERT_EQUAL(16, vec2.capacity);
    TEST_ASSERT_EQUAL(expSize, vec2.size);
    TEST_ASSERT_EQUAL_PTR(p1, vec2.array);

    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(0, vec.size);
    TEST_ASSERT_EQUAL_PTR(p2, vec.array);
    freeVector(&vec2);
}

void vectorShouldBeClear()
{
    initializeWithElements();
    clearVector(&vec);

    TEST_ASSERT_EQUAL(16, vec.capacity);
    TEST_ASSERT_EQUAL(0, vec.size);
    TEST_ASSERT_EMPTY(vec.array);
}

void vectorShouldShrinkToFit()
{
    initializeWithElements();
    shrinkToFitVector(&vec);
    TEST_ASSERT_EQUAL(expSize, vec.capacity);
    TEST_ASSERT_EQUAL(expSize, vec.size);
}

void vectorShouldReturnTrueIfItIsEmpty()
{
    TEST_ASSERT_EQUAL(1, isEmptyVector(&vec));
    TEST_ASSERT_EQUAL(0, vec.size);
}

void vectorShouldReturnFalseIfItIsNotEmpty()
{
    initializeWithElements();
    TEST_ASSERT_EQUAL(0, isEmptyVector(&vec));
    TEST_ASSERT_EQUAL(expSize, vec.size);
}

void vectorShouldIncreaseCapacityIfResquestedResizeIsGreaterThanActual()
{
    int newSize = 20;
    initializeWithElements();
    resizeVector(&vec, newSize, &c);

    TEST_ASSERT_EQUAL(newSize, vec.capacity);
    TEST_ASSERT_EQUAL(newSize, vec.size);
}

void vectorShouldDecreaseSizeIfResquestedResizeIsLessThanActual()
{
    int newSize = expSize - 1;
    initializeWithElements();
    int oldCap = vec.capacity;
    resizeVector(&vec, newSize, &c);

    TEST_ASSERT_EQUAL(oldCap, vec.capacity);
    TEST_ASSERT_EQUAL(newSize, vec.size);
}

void vectorShouldGiveTheCorrectElement()
{
    initializeWithElements();

    TEST_ASSERT_EQUAL(a, *((int *)atVector(vec, 0)));
    TEST_ASSERT_EQUAL(b, *((int *)atVector(vec, 1)));
}
int main()
{
    UNITY_BEGIN();
    RUN_TEST(vectorShouldBeInitialized);
    RUN_TEST(vectorShouldPushBackElement);
    RUN_TEST(vectorShouldPopBackElement);
    RUN_TEST(vectorShouldInsertElement);
    RUN_TEST(vectorShouldInsertElementInTheBegin);
    RUN_TEST(vectorShouldInsertElementInTheEnd);
    RUN_TEST(vectorShouldInsertNElements);
    RUN_TEST(vectorShouldInsertNElementsInTheBegin);
    RUN_TEST(vectorShouldInsertNElementsInTheEnd);
    RUN_TEST(vectorShouldInsertArray);
    RUN_TEST(vectorShouldInsertArrayInTheBegin);
    RUN_TEST(vectorShouldInsertArrayInTheEnd);
    RUN_TEST(vectorShouldEraseElements);
    RUN_TEST(vectorShouldEraseAllElements);
    RUN_TEST(vectorsShouldSwap);
    RUN_TEST(vectorShouldBeClear);
    RUN_TEST(vectorShouldShrinkToFit);
    RUN_TEST(vectorShouldReturnTrueIfItIsEmpty);
    RUN_TEST(vectorShouldReturnFalseIfItIsNotEmpty);
    RUN_TEST(vectorShouldIncreaseCapacityIfResquestedResizeIsGreaterThanActual);
    RUN_TEST(vectorShouldDecreaseSizeIfResquestedResizeIsLessThanActual);
    RUN_TEST(vectorShouldGiveTheCorrectElement);
    return UNITY_END();
}