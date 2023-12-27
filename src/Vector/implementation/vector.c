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
        .size = 0,
        .capacity = INIT_ARRAY_SIZE_VECTOR};
}

static void expandVector(Vector *vec, int newCap)
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
    if (vec->size >= vec->capacity)
        expandVector(vec, vec->capacity * 2);

    vec->array[vec->size] = item;
    vec->size++;
}

void insertVector(Vector *vec, void *item, int index)
{
    if (index > vec->size || index < 0)
        return;

    if (vec->size >= vec->capacity)
        expandVector(vec, vec->capacity * 2);

    memcpy(vec->array + index + 1,
           vec->array + index,
           sizeof(void *) * (vec->size - index));
    vec->array[index] = item;
    vec->size++;
}

void insertNVector(Vector *vec, void *item, int n, int index)
{
    if (index > vec->size + n - 1 || index < 0)
        return;

    if (vec->size + n >= vec->capacity)
        expandVector(vec, (vec->capacity * 2) + n);

    memcpy(vec->array + index + n,
           vec->array + index,
           sizeof(void *) * (vec->size - index));

    for (int i = 0; i < n; i++)
        vec->array[index + i] = item;
    vec->size += n;
}

void insertArrayVector(Vector *vec, void **items, int firstIndex, int lastIndex, int index)
{
    int n = lastIndex - firstIndex;
    if (index > vec->size || index < 0 || firstIndex > lastIndex)
        return;

    if (vec->size + n >= vec->capacity)
        expandVector(vec, (vec->capacity * 2) + n);

    memcpy(vec->array + index + n,
           vec->array + index,
           sizeof(void *) * (vec->size - index));

    for (int i = 0; i < n; i++)
        vec->array[index + i] = items[firstIndex + i];
    vec->size += n;
}

void erase(Vector *vec, int firstIndex, int lastIndex)
{
    int eraseSize = lastIndex - firstIndex;
    if (eraseSize > vec->size)
        return;

    if (lastIndex > vec->size || firstIndex > vec->size - 1)
        return;

    memcpy(vec->array + firstIndex,
           vec->array + lastIndex,
           sizeof(void *) * (vec->size - lastIndex));

    memset(vec->array + vec->size - eraseSize,
           0,
           sizeof(void *) * eraseSize);
    vec->size -= eraseSize;
}

void *popBackVector(Vector *vec)
{
    if (vec->size <= 0)
        return NULL;

    void *popped = vec->array[vec->size - 1];
    vec->array[vec->size - 1] = NULL;
    vec->size--;
    return popped;
}

void freeVector(Vector *vec)
{
    free(vec->array);
}
