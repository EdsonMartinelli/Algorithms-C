#include <stdio.h>

#define ARRAY_SIZE 10

void initializeArray(int *, int);
void printArray(int *, int);
void maxHeapify(int *, int, int, int); // Crescent
void minHeapify(int *, int, int, int); // Decrescent
void buildHeap(int *, int, void (*function)(int *, int, int, int));
void heapSort(int *, int, void (*function)(int *, int, int, int));

int main()
{
    int array[ARRAY_SIZE];
    initializeArray(array, ARRAY_SIZE);
    printf("Original Array: \n");
    printArray(array, ARRAY_SIZE);
    printf("After HeapSort: \n");
    heapSort(array, ARRAY_SIZE, &minHeapify);
    printArray(array, ARRAY_SIZE);
    return 0;
}

void initializeArray(int *array, int arraySize)
{
    for (int count = 0; count < arraySize; count++)
        array[count] = count + 1;
}

void printArray(int *array, int arraySize)
{
    for (int count = 0; count < arraySize; count++)
        printf("%d ", array[count]);
    printf("\n");
}

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
