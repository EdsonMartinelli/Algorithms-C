#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#define MIN_PRIORITY_QUEUE_SIZE 16

typedef struct
{
    void *data;
    int key;
} ItemPriorityQueue;

typedef struct
{
    ItemPriorityQueue **queue;
    int size;
    int capacity;
} PriorityQueue;

void initPriorityQueue(PriorityQueue *);
ItemPriorityQueue *addPriorityQueue(PriorityQueue *, ItemPriorityQueue *);
ItemPriorityQueue *extractMaxPriorityQueue(PriorityQueue *);
void printPriorityQueue(PriorityQueue);
void destroyPriorityQueue(PriorityQueue *);

#endif