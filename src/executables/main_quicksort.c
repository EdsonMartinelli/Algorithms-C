#include <stdio.h>
#include "../headers/quicksort.h"

#define ARRAY_SIZE 10

void initValues(int *array, int arraySize);
void initArray(int **array, int *values, int arraySize);
void printArrayQuickSort(void **array, int arraySize);

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
    printArrayQuickSort((void **)array, ARRAY_SIZE);
    printf("After QuickSort: \n");
    quickSort((void **)array, ARRAY_SIZE, &comparator);
    printArrayQuickSort((void **)array, ARRAY_SIZE);
    printf("After QuickSort Decrescent: \n");
    quickSortDecrescent((void **)array, ARRAY_SIZE, &comparator);
    printArrayQuickSort((void **)array, ARRAY_SIZE);
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

void printArrayQuickSort(void **array, int arraySize)
{
    for (int count = 0; count < arraySize; count++)
        printf("%i ", *((int *)array[count]));
    printf("\n");
}
