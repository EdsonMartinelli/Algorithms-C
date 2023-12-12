#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

typedef struct
{
    void *data;
    int key;
} Item;

typedef struct
{
    Item **queue;
    int size;
    int capacity;
} PriorityQueue;

void initPriorityQueue(PriorityQueue *, Item **, int);
void maxHeapifyBottomUp(PriorityQueue *, int, Item *);
void maxHeapifyTopDown(PriorityQueue *, int, Item *);
Item *addPriorityQueue(PriorityQueue *, Item *);
Item *extractMaxPriorityQueue(PriorityQueue *);
void printPriorityQueue(PriorityQueue *);

#endif