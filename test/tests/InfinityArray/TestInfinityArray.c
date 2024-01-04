#include <stdlib.h>
#include "../../Unity/unity.h"
#include "../../../src/InfinityArray/implementation/infinityarray.h"
#include "../../../src/Utils/utils.h"

#define expSize 10

InfinityArray array;
int items[expSize];

void setUp()
{
    initInfinityArray(&array);
}

void tearDown()
{
    destroyInfinityArray(&array);
}

void infinityArrayShouldBeInitializedCorrecty()
{
    TEST_ASSERT_EQUAL(INIT_INFINITY_ARRAY_SIZE, array.capacity);
    TEST_ASSERT_EQUAL(-1, array.lastElementIndex);
    TEST_ASSERT_NOT_NULL(array.array);
    TEST_ASSERT_EMPTY(array.array);
}

void infinityArrayShouldPushItemsCorrecty()
{
    for (int i = 0; i < expSize; i++)
    {
        items[i] = i;
        void *returnItem = pushInfinityArray(&array, &items[i]);
        TEST_ASSERT_NOT_NULL(returnItem);
    }

    TEST_ASSERT_EQUAL(INIT_INFINITY_ARRAY_SIZE, array.capacity);
    TEST_ASSERT_EQUAL(expSize - 1, array.lastElementIndex);

    for (int i = 0; i < expSize; i++)
    {
        TEST_ASSERT_EQUAL(items[i], *((int *)array.array[i]));
    }
}

void infinityArrayPushItemsShouldIncreaseCapacityWhenItIsFull()
{
    int n = INIT_INFINITY_ARRAY_SIZE + 1;
    int itemsMax[n];
    for (int i = 0; i < n; i++)
    {
        itemsMax[i] = i;
        void *returnItem = pushInfinityArray(&array, &itemsMax[i]);
        TEST_ASSERT_NOT_NULL(returnItem);
    }

    TEST_ASSERT_EQUAL(INIT_INFINITY_ARRAY_SIZE * 2, array.capacity);
    TEST_ASSERT_EQUAL(n - 1, array.lastElementIndex);

    for (int i = 0; i < n; i++)
    {
        TEST_ASSERT_EQUAL(itemsMax[i], *((int *)array.array[i]));
    }
}

void infinityArrayShouldSetItemsCorrecty()
{
    int item = 10;
    int index = 6;
    void *returnItem = setInfinityArray(&array, &item, index);
    TEST_ASSERT_NOT_NULL(returnItem);

    TEST_ASSERT_EQUAL(INIT_INFINITY_ARRAY_SIZE, array.capacity);
    TEST_ASSERT_EQUAL(index, array.lastElementIndex);
    TEST_ASSERT_EQUAL(item, *((int *)array.array[index]));

    int item2 = 20;
    int index2 = 12;
    void *returnItem2 = setInfinityArray(&array, &item2, index2);
    TEST_ASSERT_NOT_NULL(returnItem2);

    TEST_ASSERT_EQUAL(INIT_INFINITY_ARRAY_SIZE, array.capacity);
    TEST_ASSERT_EQUAL(index2, array.lastElementIndex);
    TEST_ASSERT_EQUAL(item2, *((int *)array.array[index2]));
}

void infinityArraySetItemsShouldIncreaseCapacityWhenIndexIsGreaterThanCapacity()
{
    int index = INIT_INFINITY_ARRAY_SIZE + 1;
    int item = 10;

    void *returnItem = setInfinityArray(&array, &item, index);
    TEST_ASSERT_NOT_NULL(returnItem);

    TEST_ASSERT_EQUAL((index + 1), array.capacity);
    TEST_ASSERT_EQUAL(index, array.lastElementIndex);
    TEST_ASSERT_EQUAL(item, *((int *)array.array[index]));
}

void infinityArrayShouldPushItemsCorrectyAfterSetItem()
{
    int index = INIT_INFINITY_ARRAY_SIZE + 1;
    int item = 10;

    void *returnItem = setInfinityArray(&array, &item, index);
    TEST_ASSERT_NOT_NULL(returnItem);

    int newCap = index + 1;
    TEST_ASSERT_EQUAL(newCap, array.capacity);
    TEST_ASSERT_EQUAL(index, array.lastElementIndex);
    TEST_ASSERT_EQUAL(item, *((int *)array.array[index]));

    for (int i = 0; i < expSize; i++)
    {
        items[i] = i;
        returnItem = pushInfinityArray(&array, &items[i]);
        TEST_ASSERT_NOT_NULL(returnItem);
    }

    TEST_ASSERT_EQUAL(newCap * 2, array.capacity);
    TEST_ASSERT_EQUAL(index + expSize, array.lastElementIndex);

    for (int i = index + 1; i <= expSize; i++)
    {
        TEST_ASSERT_EQUAL(items[i], *((int *)array.array[i]));
    }
}

void infinityArrayShouldPopItemCorrecty()
{
    for (int i = 0; i < expSize; i++)
    {
        items[i] = i;
        void *returnItem = pushInfinityArray(&array, &items[i]);
        TEST_ASSERT_NOT_NULL(returnItem);
    }

    TEST_ASSERT_EQUAL(INIT_INFINITY_ARRAY_SIZE, array.capacity);
    TEST_ASSERT_EQUAL(expSize - 1, array.lastElementIndex);

    void *lastItem = array.array[array.lastElementIndex];
    void *lastItemPopped = popInfinityArray(&array);
    TEST_ASSERT_EQUAL_PTR(lastItem, lastItemPopped);

    TEST_ASSERT_EQUAL(INIT_INFINITY_ARRAY_SIZE, array.capacity);
    TEST_ASSERT_EQUAL(expSize - 2, array.lastElementIndex);
    TEST_ASSERT_NULL(array.array[array.lastElementIndex + 1]);
}

void infinityArrayShouldPopItemCorrectyAfterSetItem()
{
    for (int i = 0; i < expSize; i++)
    {
        items[i] = i;
        void *returnItem = pushInfinityArray(&array, &items[i]);
        TEST_ASSERT_NOT_NULL(returnItem);
    }

    int index = INIT_INFINITY_ARRAY_SIZE + 1;
    int item = 10;

    void *returnItem = setInfinityArray(&array, &item, index);
    TEST_ASSERT_NOT_NULL(returnItem);

    TEST_ASSERT_EQUAL((index + 1), array.capacity);
    TEST_ASSERT_EQUAL(index, array.lastElementIndex);

    void *lastItem = array.array[array.lastElementIndex];
    void *lastItemPopped = popInfinityArray(&array);
    TEST_ASSERT_EQUAL_PTR(lastItem, lastItemPopped);

    TEST_ASSERT_EQUAL((index + 1), array.capacity);
    TEST_ASSERT_EQUAL(index - 1, array.lastElementIndex);
    TEST_ASSERT_NULL(array.array[array.lastElementIndex + 1]);
}

void infinityArrayGetItemShouldReturnTheCorrectValue()
{
    for (int i = 0; i < expSize; i++)
    {
        items[i] = i;
        void *returnItem = pushInfinityArray(&array, &items[i]);
        TEST_ASSERT_NOT_NULL(returnItem);
    }

    void *lastItem = array.array[array.lastElementIndex];
    void *itemGet = getInfinityArray(&array, expSize - 1);

    TEST_ASSERT_EQUAL_PTR(lastItem, itemGet);

    int index = INIT_INFINITY_ARRAY_SIZE + 1;
    int item = 10;

    void *returnItem = setInfinityArray(&array, &item, index);
    TEST_ASSERT_NOT_NULL(returnItem);

    lastItem = array.array[array.lastElementIndex];
    itemGet = getInfinityArray(&array, index);

    TEST_ASSERT_EQUAL_PTR(lastItem, itemGet);
}

void infinityArrayLengthShouldBeCorrect()
{
    for (int i = 0; i < expSize; i++)
    {
        items[i] = i;
        void *returnItem = pushInfinityArray(&array, &items[i]);
        TEST_ASSERT_NOT_NULL(returnItem);
    }

    int length = lengthInfinityArray(array);
    TEST_ASSERT_EQUAL(expSize, length);

    int index = INIT_INFINITY_ARRAY_SIZE + 1;
    int item = 10;

    void *returnItem = setInfinityArray(&array, &item, index);
    TEST_ASSERT_NOT_NULL(returnItem);

    length = lengthInfinityArray(array);
    TEST_ASSERT_EQUAL(index + 1, length);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(infinityArrayShouldBeInitializedCorrecty);
    RUN_TEST(infinityArrayShouldPushItemsCorrecty);
    RUN_TEST(infinityArrayPushItemsShouldIncreaseCapacityWhenItIsFull);
    RUN_TEST(infinityArrayShouldSetItemsCorrecty);
    RUN_TEST(infinityArraySetItemsShouldIncreaseCapacityWhenIndexIsGreaterThanCapacity);
    RUN_TEST(infinityArrayShouldPushItemsCorrectyAfterSetItem);
    RUN_TEST(infinityArrayShouldPopItemCorrecty);
    RUN_TEST(infinityArrayShouldPopItemCorrectyAfterSetItem);
    RUN_TEST(infinityArrayGetItemShouldReturnTheCorrectValue);
    RUN_TEST(infinityArrayLengthShouldBeCorrect);
    return UNITY_END();
}