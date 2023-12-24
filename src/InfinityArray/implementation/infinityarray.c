#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infinityarray.h"

void initializeInfinityArray(InfinityArray *vec)
{
    void **array = (void **)malloc(sizeof(void *) * INIT_INFINITY_ARRAY_SIZE);
    if (array == NULL)
    {
        printf("Memory Allocate Failure.");
        exit(EXIT_FAILURE);
    }
    memset(array, 0, sizeof(void *) * INIT_INFINITY_ARRAY_SIZE);
    *vec = (InfinityArray){
        .array = array,
        .lastElementIndex = -1,
        .capacity = INIT_INFINITY_ARRAY_SIZE};
}

void expandInfinityArray(InfinityArray *vec, int newCap)
{
    void **newArray = (void **)realloc(vec->array, sizeof(void *) * newCap);
    if (newArray == NULL)
    {
        printf("Memory Allocate Failure.");
        exit(EXIT_FAILURE);
    }
    memset(newArray + vec->capacity, 0, sizeof(void *) * (newCap - vec->capacity));
    vec->array = newArray;
    vec->capacity = newCap;
}

void pushInfinityArray(InfinityArray *vec, void *item)
{

    if (vec->lastElementIndex >= vec->capacity)
        expandInfinityArray(vec, vec->capacity * 2);

    vec->array[vec->lastElementIndex + 1] = item;
    vec->lastElementIndex++;
}

void *popInfinityArray(InfinityArray *vec)
{

    if (vec->lastElementIndex < 0)
        return NULL;

    void *temp = vec->array[vec->lastElementIndex];
    vec->array[vec->lastElementIndex] = NULL;
    vec->lastElementIndex--;
    return temp;
}

void setInfinityArray(InfinityArray *vec, void *item, int index)
{
    if (index < 0)
    {
        printf("Array Out of Bounds!\n");
        exit(EXIT_FAILURE);
    }
    if (index >= vec->capacity)
        expandInfinityArray(vec, index + (index / 2));

    vec->array[index] = item;
    if (index > vec->lastElementIndex)
        vec->lastElementIndex = index;
}

void *getInfinityArray(InfinityArray *vec, int index)
{
    if (index < 0)
    {
        printf("Array Out of Bounds!\n");
        exit(EXIT_FAILURE);
    }

    /*if (index >= vec->capacity)
    {
        printf("Array Out of Bounds!\n");
        exit(EXIT_FAILURE);
    }*/

    if (index >= vec->capacity)
        return NULL;

    return vec->array[index];
}

int lengthInfinityArray(InfinityArray vec)
{
    return vec.lastElementIndex + 1;
}

void destroyInfinityArray(InfinityArray *vec)
{
    free(vec->array);
}
