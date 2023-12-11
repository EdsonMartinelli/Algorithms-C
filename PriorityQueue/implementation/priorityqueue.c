#include <stdio.h>
#include "priorityqueue.h"

void initializePriorityQueue(PriorityQueue *pq, Item *queue, int cap)
{
    (*pq) = (PriorityQueue){.queue = queue, .size = 0, .capacity = cap};
}

void printQueue(PriorityQueue *pq)
{
    for (int i = 0; i < (*pq).size; i++)
        printf("%i ", (*pq).queue[i].key);
    printf("\n");
}

void maxHeapifyBottomUp(PriorityQueue *pq, int index, Item targetItem)
{
    if (index > (*pq).size)
        return;
    int father = index % 2 == 0 ? (index / 2) - 1 : index / 2;
    if (father < 0 || targetItem.key < (*pq).queue[father].key)
    {
        (*pq).queue[index] = targetItem;
        return;
    }
    (*pq).queue[index] = (*pq).queue[father];
    maxHeapifyBottomUp(pq, father, targetItem);
}

void maxHeapifyTopDown(PriorityQueue *pq, int index, Item targetItem)
{
    if (index > (*pq).size)
        return;

    int max = index;
    int left = (index * 2) + 1;
    int right = (index * 2) + 2;

    if (left < (*pq).size && (*pq).queue[left].key > targetItem.key)
    {
        max = left;
    }

    if (right < (*pq).size && (*pq).queue[right].key > (*pq).queue[left].key)
        max = right;

    if (max == index)
    {
        (*pq).queue[max] = targetItem;
        return;
    }

    (*pq).queue[index] = (*pq).queue[max];
    maxHeapifyTopDown(pq, max, targetItem);
}

void add(PriorityQueue *pq, Item item)
{
    if ((*pq).size >= (*pq).capacity)
        return;

    (*pq).queue[(*pq).size] = item;
    maxHeapifyBottomUp(pq, (*pq).size, (*pq).queue[(*pq).size]);
    (*pq).size++;
}

Item extractMax(PriorityQueue *pq)
{
    Item temp = (*pq).queue[0];
    (*pq).queue[0] = (*pq).queue[(*pq).size - 1];
    (*pq).queue[(*pq).size - 1] = temp;
    (*pq).size--;
    maxHeapifyTopDown(pq, 0, (*pq).queue[0]);
    return temp;
}
