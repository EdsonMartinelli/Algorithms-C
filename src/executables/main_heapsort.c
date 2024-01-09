#include <stdio.h>
#include "../headers/heapsort.h"

#define ARRAY_SIZE 10

void initValues(int *array, int arraySize);
void initArray(int **array, int *values, int arraySize);
void printer(void *item);

int comparator(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

int main()
{
    int values[ARRAY_SIZE];
    int *array[ARRAY_SIZE];
    initValues(values, ARRAY_SIZE);
    initArray(array, values, ARRAY_SIZE);
    printf("Original Array: \n");
    printArrayHeapSort((void **)array, ARRAY_SIZE, &printer);
    printf("After HeapSort: \n");
    heapSort((void **)array, ARRAY_SIZE, &comparator);
    printArrayHeapSort((void **)array, ARRAY_SIZE, &printer);
    printf("After HeapSort Decrescent: \n");
    heapSortDecrescent((void **)array, ARRAY_SIZE, &comparator);
    printArrayHeapSort((void **)array, ARRAY_SIZE, &printer);
    return 0;
}

void initValues(int *array, int arraySize)
{
    for (int count = 0; count < arraySize; count++)
        array[count] = count + 1;
}

void initArray(int **array, int *values, int arraySize)
{
    for (int count = 0; count < arraySize; count++)
        array[count] = &values[count];
}

void printer(void *item)
{
    printf("%i ", *((int *)item));
}