#include <stdio.h>
#include "../headers/heapsort.h"

#define ARRAY_SIZE 10

void initArray(int *, int);
int main()
{
    int array[ARRAY_SIZE];
    initArray(array, ARRAY_SIZE);
    printf("Original Array: \n");
    printArrayHeapSort(array, ARRAY_SIZE);
    printf("After HeapSort: \n");
    heapSort(array, ARRAY_SIZE);
    printArrayHeapSort(array, ARRAY_SIZE);
    printf("After HeapSort Decrescent: \n");
    heapSortDecrescent(array, ARRAY_SIZE);
    printArrayHeapSort(array, ARRAY_SIZE);
    return 0;
}

void initArray(int *array, int arraySize)
{
    for (int count = 0; count < arraySize; count++)
        array[count] = count + 1;
}