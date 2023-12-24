#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

void initializeVector(Vector *vec)
{
    void **array = (void **)malloc(sizeof(void *) * INIT_ARRAY_SIZE_VECTOR);
    if (array == NULL)
    {
        printf("Memory Allocate Failure.");
        exit(EXIT_FAILURE);
    }
    memset(array, 0, sizeof(void *) * INIT_ARRAY_SIZE_VECTOR);
    *vec = (Vector){
        .array = array,
        .nextElementIndex = 0,
        .capacity = INIT_ARRAY_SIZE_VECTOR};
}

void expandVector(Vector *vec, int newCap)
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

void pushBackVector(Vector *vec, void *item)
{
    if (vec->nextElementIndex >= vec->capacity)
        expandVector(vec, vec->capacity * 2);
    vec->array[vec->nextElementIndex] = item;
    vec->nextElementIndex++;
}

void pushVectorWithIndex(Vector *vec, void *item, int index)
{
    if (index >= vec->capacity)
        expandVector(vec, index + (index / 2));
    vec->array[index] = item;
    vec->nextElementIndex = index + 1;
}

void *popVectorWithIndex(Vector *vec, int index)
{
    if (index >= vec->capacity)
    {
        printf("Array Out of Bounds!\n");
        exit(EXIT_FAILURE);
    }
    void *popped = vec->array[index];
    vec->array[index] = NULL;
    return popped;
}

void freeVector(Vector *vec)
{
    free(vec->array);
}
