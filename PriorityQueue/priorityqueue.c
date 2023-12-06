#include <stdio.h>
#include <stdlib.h>

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

void initializePriorityQueue(PriorityQueue *, int);
// void maxHeapifyBottomUp(PriorityQueue *, int);
void maxHeapifyBottomUp(PriorityQueue *, int, Item);
// void maxHeapifyTopDown(PriorityQueue *, int);
void maxHeapifyTopDown(PriorityQueue *, int, Item);
void add(PriorityQueue *, Item);
Item extractMax(PriorityQueue *pq);
void printQueue(PriorityQueue *);
void freePriorityQueue(PriorityQueue *);

int main()
{
    PriorityQueue pq;
    initializePriorityQueue(&pq, 10);
    Item items[6];
    for (int i = 0; i < 6; i++)
        items[i] = (Item){.key = i + 1, .data = NULL};

    for (int i = 0; i < 6; i++)
        add(&pq, items[i]);

    printQueue(&pq);
    Item e1 = extractMax(&pq);
    printf("extract item: %i\n", e1.key);
    Item e2 = extractMax(&pq);
    printf("extract item: %i\n", e2.key);
    Item e3 = extractMax(&pq);
    printf("extract item: %i\n", e3.key);
    printQueue(&pq);
    Item x = {.key = 10, .data = NULL};
    add(&pq, x);
    printQueue(&pq);
    freePriorityQueue(&pq);
    return 0;
}

void initializePriorityQueue(PriorityQueue *pq, int cap)
{
    Item *queue = malloc(sizeof(Item) * cap);
    if (queue == NULL)
    {
    }
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

void freePriorityQueue(PriorityQueue *pq)
{
    free((*pq).queue);
}
