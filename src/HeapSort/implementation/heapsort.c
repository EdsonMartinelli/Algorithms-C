#include <stdio.h>
#include "heapsort.h"

void maxHeapify(int *array, int arraySize, int index, int targetValue)
{
    int max = index;
    int left = (index * 2) + 1;
    int right = (index * 2) + 2;

    if (left < arraySize && array[left] > targetValue)
    {
        max = left;
    }

    if (right < arraySize && array[right] > array[left])
        max = right;

    if (max == index)
    {
        array[max] = targetValue;
        return;
    }

    array[index] = array[max];
    maxHeapify(array, arraySize, max, targetValue);
}

void minHeapify(int *array, int arraySize, int index, int targetValue)
{
    int min = index;
    int left = (index * 2) + 1;
    int right = (index * 2) + 2;

    if (left < arraySize && array[left] < targetValue)
        min = left;

    if (right < arraySize && array[right] < array[left])
        min = right;

    if (min == index)
    {
        array[min] = targetValue;
        return;
    }

    array[index] = array[min];
    minHeapify(array, arraySize, min, targetValue);
}

void buildHeap(int *array, int arraySize, void (*heapifyType)(int *, int, int, int))
{
    for (int index = (arraySize / 2) - 1; index >= 0; index--)
    {
        heapifyType(array, arraySize, index, array[index]);
    }
}

void heapSort(int *array, int arraySize, void (*heapifyType)(int *, int, int, int))
{
    buildHeap(array, arraySize, heapifyType);
    for (int index = 0; index < arraySize; index++)
    {
        (*heapifyType)(array, arraySize - index, 0, array[0]);
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
}