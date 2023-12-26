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
        .lastElementIndex = -1,
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
    if (vec->lastElementIndex + 1 >= vec->capacity)
        expandVector(vec, vec->capacity * 2);

    vec->lastElementIndex++;
    vec->array[vec->lastElementIndex] = item;
}

void insertVector(Vector *vec, void *item, int index)
{
    if (index > vec->lastElementIndex + 1 || index < 0)
        return;

    if (vec->lastElementIndex + 1 >= vec->capacity)
        expandVector(vec, vec->capacity * 2);

    memcpy(vec->array + index + 1,
           vec->array + index,
           sizeof(void *) * (vec->lastElementIndex - index + 1));
    vec->array[index] = item;
    vec->lastElementIndex++;
}

void insertNVector(Vector *vec, void *item, int n, int index)
{
    if (index > vec->lastElementIndex + n || index < 0)
        return;

    if (vec->lastElementIndex + n >= vec->capacity)
        expandVector(vec, (vec->capacity * 2) + n);

    memcpy(vec->array + index + n,
           vec->array + index,
           sizeof(void *) * (vec->lastElementIndex - index + 1));

    for (int i = 0; i < n; i++)
        vec->array[index + i] = item;
    vec->lastElementIndex += n;
}

void insertArrayVector(Vector *vec, void **items, int firstIndex, int lastIndex, int index)
{
    int n = (lastIndex - firstIndex + 1);
    if (index > vec->lastElementIndex + n || index < 0 || firstIndex > lastIndex)
        return;

    if (vec->lastElementIndex + n >= vec->capacity)
        expandVector(vec, (vec->capacity * 2) + n);

    memcpy(vec->array + index + n,
           vec->array + index,
           sizeof(void *) * (vec->lastElementIndex - index + 1));

    for (int i = 0; i < n; i++)
        vec->array[index + i] = items[firstIndex + i];
    vec->lastElementIndex += n;
}

void erase(Vector *vec, int firstIndex, int lastIndex)
{
    int size = lastIndex - firstIndex + 1;
    if (size > vec->lastElementIndex + 1)
        return;

    memcpy(vec->array + firstIndex,
           vec->array + lastIndex,
           sizeof(void *) * (vec->lastElementIndex - lastIndex + 1));

    // No finished
    vec->lastElementIndex -= size;
}

void *popBackVector(Vector *vec)
{
    if (vec->lastElementIndex < 0)
        return NULL;

    void *popped = vec->array[vec->lastElementIndex];
    vec->array[vec->lastElementIndex] = NULL;
    vec->lastElementIndex--;
    return popped;
}

void freeVector(Vector *vec)
{
    free(vec->array);
}
