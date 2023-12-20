#include <stdio.h>
#include <stdlib.h>
#include "implementation/priorityqueue.h"

#define CAPACITY 10

int main()
{
    PriorityQueue pq;
    // Item **queue = malloc(sizeof(Item *) * CAPACITY);
    Item *queue[CAPACITY];
    initPriorityQueue(&pq, queue, CAPACITY);
    Item items[6];
    for (int i = 0; i < 6; i++)
        items[i] = (Item){.key = i + 1, .data = NULL};

    for (int i = 0; i < 6; i++)
        addPriorityQueue(&pq, &items[i]);

    printPriorityQueue(&pq);
    Item *e1 = extractMaxPriorityQueue(&pq);
    printf("extract item: %i\n", (*e1).key);
    Item *e2 = extractMaxPriorityQueue(&pq);
    printf("extract item: %i\n", (*e2).key);
    Item *e3 = extractMaxPriorityQueue(&pq);
    printf("extract item: %i\n", (*e3).key);
    printPriorityQueue(&pq);
    Item x = {.key = 10, .data = NULL};
    addPriorityQueue(&pq, &x);
    printPriorityQueue(&pq);
    // free(queue);
    return 0;
}