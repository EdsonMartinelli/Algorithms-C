#include <stdio.h>
#include "../headers/heapsort.h"

/*static void maxHeapify(int *array, int arraySize, int index, int targetValue)
{
    int max = index;
    int left = (index * 2) + 1;
    int right = (index * 2) + 2;

    if (left < arraySize && array[left] > targetValue)
    {
        max = left;
    }

    if (max == left)
    {
        if (right < arraySize && array[right] > array[left])
            max = right;
    }
    else
    {
        if (right < arraySize && array[right] > targetValue)
            max = right;
    }

    if (max == index)
    {
        array[max] = targetValue;
        return;
    }

    array[index] = array[max];
    maxHeapify(array, arraySize, max, targetValue);
}

static void minHeapify(int *array, int arraySize, int index, int targetValue)
{
    int min = index;
    int left = (index * 2) + 1;
    int right = (index * 2) + 2;

    if (left < arraySize && array[left] < targetValue)
        min = left;

    if (min == left)
    {
        if (right < arraySize && array[right] < array[left])
            min = right;
    }
    else
    {
        if (right < arraySize && array[right] < targetValue)
            min = right;
    }

    if (min == index)
    {
        array[min] = targetValue;
        return;
    }

    array[index] = array[min];
    minHeapify(array, arraySize, min, targetValue);
}

static void buildHeap(int *array, int arraySize, void (*heapifyType)(int *, int, int, int))
{
    for (int index = (arraySize / 2) - 1; index >= 0; index--)
    {
        heapifyType(array, arraySize, index, array[index]);
    }
}

void heapSort(int *array, int arraySize)
{
    buildHeap(array, arraySize, &maxHeapify);
    for (int index = 0; index < arraySize; index++)
    {
        maxHeapify(array, arraySize - index, 0, array[0]);
        int temp = array[0];
        array[0] = array[arraySize - index - 1];
        array[arraySize - index - 1] = temp;
    }
}

void heapSortDecrescent(int *array, int arraySize)
{
    buildHeap(array, arraySize, &minHeapify);
    for (int index = 0; index < arraySize; index++)
    {
        minHeapify(array, arraySize - index, 0, array[0]);
        int temp = array[0];
        array[0] = array[arraySize - index - 1];
        array[arraySize - index - 1] = temp;
    }
}

void printArrayHeapSort(int *array, int arraySize)
{
    for (int count = 0; count < arraySize; count++)
        printf("%d ", array[count]);
    printf("\n");
}*/

static void maxHeapify(
    void **array,
    int arraySize,
    int index,
    void *targetValue,
    int (*comparator)(void *, void *))
{
    int max = index;
    int left = (index * 2) + 1;
    int right = (index * 2) + 2;

    if (left < arraySize && comparator(array[left], targetValue) > 0)
        max = left;

    if (max == left)
    {
        if (right < arraySize && comparator(array[right], array[left]) > 0)
            max = right;
    }
    else
    {
        if (right < arraySize && comparator(array[right], targetValue) > 0)
            max = right;
    }

    if (max == index)
    {
        array[max] = targetValue;
        return;
    }

    array[index] = array[max];
    maxHeapify(array, arraySize, max, targetValue, comparator);
}

static void minHeapify(
    void **array,
    int arraySize,
    int index,
    void *targetValue,
    int (*comparator)(void *, void *))
{
    int min = index;
    int left = (index * 2) + 1;
    int right = (index * 2) + 2;

    if (left < arraySize && (*comparator)(array[left], targetValue) < 0)
        min = left;

    if (min == left)
    {
        if (right < arraySize && (*comparator)(array[right], array[left]) < 0)
            min = right;
    }
    else
    {
        if (right < arraySize && (*comparator)(array[right], targetValue) < 0)
            min = right;
    }

    if (min == index)
    {
        array[min] = targetValue;
        return;
    }

    array[index] = array[min];
    minHeapify(array, arraySize, min, targetValue, comparator);
}

static void buildHeap(
    void **array,
    int arraySize,
    void (*heapifyType)(void **, int, int, void *, int (*comparator)(void *, void *)),
    int (*comparator)(void *, void *))
{
    for (int index = (arraySize / 2) - 1; index >= 0; index--)
    {
        heapifyType(array, arraySize, index, array[index], comparator);
    }
}

void heapSort(void **array, int arraySize, int (*comparator)(void *, void *))
{
    buildHeap(array, arraySize, &maxHeapify, comparator);
    for (int index = 0; index < arraySize; index++)
    {
        maxHeapify(array, arraySize - index, 0, array[0], comparator);
        void *temp = array[0];
        array[0] = array[arraySize - index - 1];
        array[arraySize - index - 1] = temp;
    }
}

void heapSortDecrescent(void **array, int arraySize, int (*comparator)(void *, void *))
{
    buildHeap(array, arraySize, &minHeapify, comparator);
    for (int index = 0; index < arraySize; index++)
    {
        minHeapify(array, arraySize - index, 0, array[0], comparator);
        void *temp = array[0];
        array[0] = array[arraySize - index - 1];
        array[arraySize - index - 1] = temp;
    }
}

void printArrayHeapSort(void **array, int arraySize, void (*printer)(void *))
{
    for (int count = 0; count < arraySize; count++)
        (*printer)(array[count]);
    printf("\n");
}