#include <stdio.h>
#include <stdlib.h>
#include "priorityqueue.h"

// #define MIN_PRIORITY_QUEUE_SIZE 16
// #define MAX_PRIORITY_QUEUE_SIZE 1073741823

void initPriorityQueue(PriorityQueue *pq)
{
    ItemPriorityQueue **queue = malloc(sizeof(ItemPriorityQueue *) * MIN_PRIORITY_QUEUE_SIZE);
    (*pq) = (PriorityQueue){.queue = queue,
                            .size = 0,
                            .capacity = MIN_PRIORITY_QUEUE_SIZE};
}

void printPriorityQueue(PriorityQueue pq)
{
    for (int i = 0; i < pq.size; i++)
        printf("%i ", (*pq.queue[i]).key);
    printf("\n");
}

static ItemPriorityQueue **changeCapacityPriorityQueue(ItemPriorityQueue **queue, int newCap)
{
    ItemPriorityQueue **newQueue = (ItemPriorityQueue **)realloc(queue, sizeof(ItemPriorityQueue *) * newCap);
    if (newQueue == NULL)
    {
        fprintf(stderr, "Memory Reallocate Failure.");
        exit(EXIT_FAILURE);
    }
    return newQueue;
}

static void maxHeapifyBottomUp(PriorityQueue *pq, int index, ItemPriorityQueue *targetItem)
{
    int x = (*targetItem).key;
    if (index > (*pq).size)
        return;
    int father = index % 2 == 0 ? (index / 2) - 1 : index / 2;
    if (father < 0 || (*targetItem).key < (*(*pq).queue[father]).key)
    {
        (*pq).queue[index] = targetItem;
        return;
    }
    (*pq).queue[index] = (*pq).queue[father];
    maxHeapifyBottomUp(pq, father, targetItem);
}

static void maxHeapifyTopDown(PriorityQueue *pq, int index, ItemPriorityQueue *targetItem)
{
    if (index > (*pq).size)
        return;

    int max = index;
    int left = (index * 2) + 1;
    int right = (index * 2) + 2;

    if (left < (*pq).size && (*(*pq).queue[left]).key > (*targetItem).key)
        max = left;

    if (max == left)
    {
        if (right < (*pq).size && (*(*pq).queue[right]).key > (*(*pq).queue[left]).key)
            max = right;
    }
    else
    {
        if (right < (*pq).size && (*(*pq).queue[right]).key > (*targetItem).key)
            max = right;
    }

    if (max == index)
    {
        (*pq).queue[max] = targetItem;
        return;
    }

    (*pq).queue[index] = (*pq).queue[max];
    maxHeapifyTopDown(pq, max, targetItem);
}

ItemPriorityQueue *addPriorityQueue(PriorityQueue *pq, ItemPriorityQueue *item)
{
    if ((*pq).size >= (*pq).capacity)
    {
        if (pq->capacity == MAX_PRIORITY_QUEUE_SIZE)
        {
            fprintf(stderr, "Maximum Queue Capacity Reached.");
            exit(EXIT_FAILURE);
        }
        int newCap = pq->capacity * 2 > MAX_PRIORITY_QUEUE_SIZE ? MAX_PRIORITY_QUEUE_SIZE : pq->capacity * 2;
        ItemPriorityQueue **newQueue = changeCapacityPriorityQueue(pq->queue, pq->capacity * 2);
        pq->queue = newQueue;
        pq->capacity = newCap;
    }

    (*pq).queue[(*pq).size] = item;
    maxHeapifyBottomUp(pq, (*pq).size, (*pq).queue[(*pq).size]);
    (*pq).size++;
    return item;
}

ItemPriorityQueue *extractMaxPriorityQueue(PriorityQueue *pq)
{
    if (pq->size <= 0)
    {
        return NULL;
    }

    ItemPriorityQueue *temp = (*pq).queue[0];
    (*pq).queue[0] = (*pq).queue[(*pq).size - 1];
    (*pq).queue[(*pq).size - 1] = temp;
    (*pq).size--;
    maxHeapifyTopDown(pq, 0, (*pq).queue[0]);
    if ((*pq).size <= (*pq).capacity * 0.25)
    {
        if (pq->capacity > MIN_PRIORITY_QUEUE_SIZE)
        {
            int newCap = pq->capacity / 2 < MIN_PRIORITY_QUEUE_SIZE ? MIN_PRIORITY_QUEUE_SIZE : pq->capacity / 2;
            ItemPriorityQueue **newQueue = changeCapacityPriorityQueue(pq->queue, pq->capacity / 2);
            pq->queue = newQueue;
            pq->capacity = newCap;
        }
    }
    return temp;
}

void destroyPriorityQueue(PriorityQueue *pq)
{
    free(pq->queue);
}