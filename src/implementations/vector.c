#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/vector.h"

void initVector(Vector *vec)
{
    void **array = (void **)malloc(sizeof(void *) * INIT_VECTOR_SIZE);
    if (array == NULL)
    {
        fprintf(stderr, "Memory Allocate Failure.");
        exit(EXIT_FAILURE);
    }
    memset(array, 0, sizeof(void *) * INIT_VECTOR_SIZE);
    *vec = (Vector){
        .array = array,
        .size = 0,
        .capacity = INIT_VECTOR_SIZE};
}

static void **changeCapacityVector(Vector *vec, int newCap)
{
    void **newArray = (void **)realloc(vec->array, sizeof(void *) * newCap);
    if (newArray == NULL)
    {
        fprintf(stderr, "Memory Reallocate Failure.");
        exit(EXIT_FAILURE);
    }
    return newArray;
}

static void expandCapacityVector(Vector *vec, int newCap)
{
    void **newArray = changeCapacityVector(vec, newCap);
    memset(newArray + vec->capacity,
           0,
           sizeof(void *) * (newCap - vec->capacity));
    vec->array = newArray;
    vec->capacity = newCap;
}

static void shrinkCapacityVector(Vector *vec, int newCap)
{
    void **newArray = changeCapacityVector(vec, newCap);
    vec->array = newArray;
    vec->capacity = newCap;
}

void pushBackVector(Vector *vec, void *item)
{
    if (vec->size >= vec->capacity)
        expandCapacityVector(vec, vec->capacity * 2);

    vec->array[vec->size] = item;
    vec->size++;
}

void insertVector(Vector *vec, void *item, int index)
{
    if (index > vec->size || index < 0)
        return;

    if (vec->size >= vec->capacity)
        expandCapacityVector(vec, vec->capacity * 2);

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
        expandCapacityVector(vec, (vec->capacity * 2) + n);

    memcpy(vec->array + index + n,
           vec->array + index,
           sizeof(void *) * (vec->size - index));

    for (int i = 0; i < n; i++)
        vec->array[index + i] = item;
    vec->size += n;
}

void insertArrayVector(
    Vector *vec,
    void **items,
    int firstIndex,
    int lastIndex,
    int index)
{
    int n = lastIndex - firstIndex;

    if (index > vec->size || index < 0 || firstIndex > lastIndex)
        return;

    if (vec->size + n >= vec->capacity)
        expandCapacityVector(vec, (vec->capacity * 2) + n);

    memcpy(vec->array + index + n,
           vec->array + index,
           sizeof(void *) * (vec->size - index));

    for (int i = 0; i < n; i++)
        vec->array[index + i] = items[firstIndex + i];
    vec->size += n;
}

void eraseVector(Vector *vec, int firstIndex, int lastIndex)
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

void swapVector(Vector *vec1, Vector *vec2)
{
    Vector tempVec = (Vector){
        .array = vec2->array,
        .size = vec2->size,
        .capacity = vec2->capacity};

    *vec2 = (Vector){
        .array = vec1->array,
        .size = vec1->size,
        .capacity = vec1->capacity};

    *vec1 = (Vector){
        .array = tempVec.array,
        .size = tempVec.size,
        .capacity = tempVec.capacity};
}

void clearVector(Vector *vec)
{
    void **newArray = changeCapacityVector(vec, INIT_VECTOR_SIZE);
    memset(newArray, 0, sizeof(void *) * INIT_VECTOR_SIZE);
    vec->array = newArray;
    vec->size = 0;
    vec->capacity = INIT_VECTOR_SIZE;
}

void shrinkToFitVector(Vector *vec)
{
    if (vec->size == vec->capacity)
        return;
    shrinkCapacityVector(vec, vec->size);
}

void reserveVector(Vector *vec, int n)
{
    if (vec->capacity >= n)
        return;

    expandCapacityVector(vec, n);
}

bool isVectorEmpty(Vector vec)
{
    if (vec.size == 0)
        return true;
    return false;
}

void *atVector(Vector vec, int index)
{
    return vec.array[index];
}

void resizeVector(Vector *vec, int n, void *initItem)
{
    if (n > vec->capacity)
        expandCapacityVector(vec, n);

    if (n > vec->size)
    {
        for (int i = 0; i < n - vec->size; i++)
            vec->array[vec->size + i] = initItem;
        vec->size = n;
    }

    if (n < vec->size)
    {
        memset(vec->array + n, 0, sizeof(void *) * (vec->size - n));
        vec->size = n;
    }
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
