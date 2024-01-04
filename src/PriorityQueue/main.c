#include <stdio.h>
#include <stdlib.h>
#include "implementation/priorityqueue.h"

#define ITEM_NUMBER 20

void printPriorityQueueData(PriorityQueue);

int main()
{
    PriorityQueue pq;
    initPriorityQueue(&pq);
    printf("CAPACITY: %i\n", pq.capacity);
    ItemPriorityQueue items[ITEM_NUMBER];
    for (int i = 0; i < ITEM_NUMBER; i++)
        items[i] = (ItemPriorityQueue){.key = i + 1, .data = "Element"};

    for (int i = 0; i < ITEM_NUMBER; i++)
        addPriorityQueue(&pq, &items[i]);

    printPriorityQueue(pq);
    printf("CAPACITY: %i\n", pq.capacity);
    ItemPriorityQueue *e1 = extractMaxPriorityQueue(&pq);
    printf("extract item: %i\n", (*e1).key);
    ItemPriorityQueue *e2 = extractMaxPriorityQueue(&pq);
    printf("extract item: %i\n", (*e2).key);
    ItemPriorityQueue *e3 = extractMaxPriorityQueue(&pq);
    printf("extract item: %i\n", (*e3).key);
    printPriorityQueue(pq);
    ItemPriorityQueue x = {.key = 10, .data = "New Element"};
    addPriorityQueue(&pq, &x);
    printPriorityQueue(pq);
    printf("CAPACITY: %i\n", pq.capacity);
    printPriorityQueueData(pq);
    destroyPriorityQueue(&pq);
    return 0;
}

void printPriorityQueueData(PriorityQueue pq)
{
    printf("\nDATA: \n");
    for (int i = 0; i < pq.size; i++)
        printf("%i :  %s \n", (*pq.queue[i]).key, (char *)(*pq.queue[i]).data);
}