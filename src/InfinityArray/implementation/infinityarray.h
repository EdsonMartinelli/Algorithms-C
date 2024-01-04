#ifndef INFINITY_ARRAY_H
#define INFINITY_ARRAY_H

#define INIT_INFINITY_ARRAY_SIZE 16

typedef struct
{
    void **array;
    int lastElementIndex;
    int capacity;
} InfinityArray;

void initInfinityArray(InfinityArray *);
void *pushInfinityArray(InfinityArray *, void *);
void *popInfinityArray(InfinityArray *);
void *setInfinityArray(InfinityArray *, void *, int);
void *getInfinityArray(InfinityArray *, int);
void destroyInfinityArray(InfinityArray *);
int lengthInfinityArray(InfinityArray);

#endif