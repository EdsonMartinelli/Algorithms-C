#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

typedef struct
{
    void *data;
    int key;
} Item;

typedef struct
{
    Item *queue;
    int size;
    int capacity;
} PriorityQueue;

void initializePriorityQueue(PriorityQueue *, Item *, int);
void maxHeapifyBottomUp(PriorityQueue *, int, Item);
void maxHeapifyTopDown(PriorityQueue *, int, Item);
void add(PriorityQueue *, Item);
Item extractMax(PriorityQueue *pq);
void printQueue(PriorityQueue *);

#endif