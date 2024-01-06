#include <stdlib.h>
#include "../Unity/unity.h"
#include "../../src/headers/heapsort.h"
#include "../../src/Utils/utils.h"

#define expSize 10

void setUp() {}

void tearDown() {}

static void initArray(int *array, int arraySize)
{
    for (int count = 0; count < arraySize; count++)
        array[count] = randomIntNumber(-100, 100, count);
}

void heapSortShouldOrderCorrecty()
{
    int array[expSize];
    initArray(array, expSize);
    heapSort(array, expSize);
    for (int i = 0; i < expSize - 1; i++)
        TEST_ASSERT_GREATER_OR_EQUAL_INT32(array[i], array[i + 1]);
}

void heapSortDecrescentShouldOrderCorrecty()
{
    int array[expSize];
    initArray(array, expSize);
    heapSortDecrescent(array, expSize);
    for (int i = 0; i < expSize - 1; i++)
        TEST_ASSERT_LESS_OR_EQUAL_INT32(array[i], array[i + 1]);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(heapSortShouldOrderCorrecty);
    RUN_TEST(heapSortDecrescentShouldOrderCorrecty);
    return UNITY_END();
}