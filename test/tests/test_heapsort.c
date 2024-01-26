#include <stdlib.h>
#include "../Unity/unity.h"
#include "../../src/headers/heapsort.h"
#include "../../src/utils/utils.h"

#define expSize 10

void setUp() {}

void tearDown() {}

static void initValues(int *array, int arraySize)
{
    for (int count = 0; count < arraySize; count++)
        array[count] = randomIntNumber(-100, 100, count);
}

static void initArray(int **array, int *values, int arraySize)
{
    for (int count = 0; count < arraySize; count++)
        array[count] = &values[count];
}

int comparator(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

void heapSortShouldOrderCorrecty()
{
    int values[expSize];
    int *array[expSize];
    initValues(values, expSize);
    initArray(array, values, expSize);

    heapSort((void **)array, expSize, &comparator);
    for (int i = 0; i < expSize - 1; i++)
        TEST_ASSERT_GREATER_OR_EQUAL_INT32(*((int *)array[i]), *((int *)array[i + 1]));
}

void heapSortDecrescentShouldOrderCorrecty()
{
    int values[expSize];
    int *array[expSize];
    initValues(values, expSize);
    initArray(array, values, expSize);

    heapSortDecrescent((void **)array, expSize, &comparator);
    for (int i = 0; i < expSize - 1; i++)
        TEST_ASSERT_LESS_OR_EQUAL_INT32(*((int *)array[i]), *((int *)array[i + 1]));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(heapSortShouldOrderCorrecty);
    RUN_TEST(heapSortDecrescentShouldOrderCorrecty);
    return UNITY_END();
}