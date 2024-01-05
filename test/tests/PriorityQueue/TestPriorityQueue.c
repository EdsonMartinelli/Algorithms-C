#include <stdlib.h>
#include "../../Unity/unity.h"
#include "../../../src/headers/priorityqueue.h"
#include "../../../src/Utils/utils.h"

#define expSize 10

PriorityQueue pq;
ItemPriorityQueue items[expSize];

void setUp()
{
    initPriorityQueue(&pq);
}

void tearDown()
{
    destroyPriorityQueue(&pq);
}

void priorityQueueShouldBeInitializedCorrecty()
{
    TEST_ASSERT_EQUAL(MIN_PRIORITY_QUEUE_SIZE, pq.capacity);
    TEST_ASSERT_EQUAL(0, pq.size);
    TEST_ASSERT_NOT_NULL(pq.queue);
}

void priorityQueueShouldAddItemsCorrecty()
{
    for (int i = 0; i < expSize; i++)
    {
        items[i] = (ItemPriorityQueue){.key = randomIntNumber(-100, 100, i),
                                       .data = NULL};
        addPriorityQueue(&pq, &items[i]);
    }

    TEST_ASSERT_EQUAL(MIN_PRIORITY_QUEUE_SIZE, pq.capacity);
    TEST_ASSERT_EQUAL(expSize, pq.size);

    for (int i = 0; i < (expSize - 1) / 2; i++)
    {
        TEST_ASSERT_LESS_OR_EQUAL_INT32((*pq.queue[i]).key, (*pq.queue[(i * 2) + 1]).key);
        TEST_ASSERT_LESS_OR_EQUAL_INT32((*pq.queue[i]).key, (*pq.queue[(i * 2) + 2]).key);
    }
}

void priorityQueueShouldExtractTheCorrectItem()
{
    for (int i = 0; i < expSize; i++)
    {
        items[i] = (ItemPriorityQueue){.key = randomIntNumber(-100, 100, i),
                                       .data = NULL};
        addPriorityQueue(&pq, &items[i]);
    }

    ItemPriorityQueue *first = pq.queue[0];
    ItemPriorityQueue *firstExtract = extractMaxPriorityQueue(&pq);

    TEST_ASSERT_EQUAL(MIN_PRIORITY_QUEUE_SIZE, pq.capacity);
    TEST_ASSERT_EQUAL(expSize - 1, pq.size);
    TEST_ASSERT_EQUAL_PTR(first, firstExtract);

    for (int i = 0; i < (expSize - 2) / 2; i++)
    {
        TEST_ASSERT_LESS_OR_EQUAL_INT32((*pq.queue[i]).key, (*pq.queue[(i * 2) + 1]).key);
        TEST_ASSERT_LESS_OR_EQUAL_INT32((*pq.queue[i]).key, (*pq.queue[(i * 2) + 2]).key);
    }
}

void priorityQueueShouldExtractTheCorrectItemWithDefinedValues()
{
    int values[expSize] = {93, 56, 40, 39, 33, -99, -38, -81, 31, -46};
    for (int i = 0; i < expSize; i++)
    {
        items[i] = (ItemPriorityQueue){.key = values[i],
                                       .data = NULL};
        addPriorityQueue(&pq, &items[i]);
    }

    ItemPriorityQueue *first = pq.queue[0];
    ItemPriorityQueue *firstExtract = extractMaxPriorityQueue(&pq);

    TEST_ASSERT_EQUAL(MIN_PRIORITY_QUEUE_SIZE, pq.capacity);
    TEST_ASSERT_EQUAL(expSize - 1, pq.size);
    TEST_ASSERT_EQUAL_PTR(first, firstExtract);

    for (int i = 0; i < (expSize - 2) / 2; i++)
    {
        TEST_ASSERT_LESS_OR_EQUAL_INT32((*pq.queue[i]).key, (*pq.queue[(i * 2) + 1]).key);
        TEST_ASSERT_LESS_OR_EQUAL_INT32((*pq.queue[i]).key, (*pq.queue[(i * 2) + 2]).key);
    }
}

void priorityQueueExtractMaxShouldReturnNullIfQueueIsEmpty()
{
    ItemPriorityQueue *firstExtract = extractMaxPriorityQueue(&pq);
    TEST_ASSERT_NULL(firstExtract);
    TEST_ASSERT_EQUAL(MIN_PRIORITY_QUEUE_SIZE, pq.capacity);
}

void priorityQueueShouldDoubleItsCapacityWhenItIsFull()
{
    int n = 16 + 1;
    ItemPriorityQueue values[n];
    for (int i = 0; i < n; i++)
    {
        values[i] = (ItemPriorityQueue){.key = i,
                                        .data = NULL};
        addPriorityQueue(&pq, &values[i]);
    }
    TEST_ASSERT_EQUAL(MIN_PRIORITY_QUEUE_SIZE * 2, pq.capacity);
    TEST_ASSERT_EQUAL(n, pq.size);
}

void priorityQueueShouldDecreaseByHalfItsCapacityWhenItIsJustAQuarterOfFilled()
{
    int n = 16 + 1;
    int nExtract = 8 + 1;
    ItemPriorityQueue values[n];
    for (int i = 0; i < n; i++)
    {
        values[i] = (ItemPriorityQueue){.key = i,
                                        .data = NULL};
        addPriorityQueue(&pq, &values[i]);
    }

    for (int i = 0; i < nExtract; i++)
    {
        extractMaxPriorityQueue(&pq);
    }
    TEST_ASSERT_EQUAL(MIN_PRIORITY_QUEUE_SIZE, pq.capacity);
    TEST_ASSERT_EQUAL(n - nExtract, pq.size);
}
int main()
{
    UNITY_BEGIN();
    RUN_TEST(priorityQueueShouldBeInitializedCorrecty);
    RUN_TEST(priorityQueueShouldAddItemsCorrecty);
    RUN_TEST(priorityQueueShouldExtractTheCorrectItem);
    RUN_TEST(priorityQueueShouldExtractTheCorrectItemWithDefinedValues);
    RUN_TEST(priorityQueueExtractMaxShouldReturnNullIfQueueIsEmpty);
    RUN_TEST(priorityQueueShouldDoubleItsCapacityWhenItIsFull);
    RUN_TEST(priorityQueueShouldDecreaseByHalfItsCapacityWhenItIsJustAQuarterOfFilled);
    return UNITY_END();
}