#include <stdio.h>
#include <stdlib.h>

struct Item
{
    int key;
};

struct PriorityQueue
{
    struct Item *queue;
    int size;
    int capacity;
};

void initializePriorityQueue(struct PriorityQueue *, int);
void maxHeapifyBottomUp(struct PriorityQueue *, int);
void maxHeapifyTopDown(struct PriorityQueue *, int);
void add(struct PriorityQueue *, struct Item);
struct Item extractMax(struct PriorityQueue *pq);
void printQueue(struct PriorityQueue *);
void freePriorityQueue(struct PriorityQueue *);

int main()
{
    struct PriorityQueue pq;
    initializePriorityQueue(&pq, 10);
    struct Item t = {.key = 1};
    struct Item x = {.key = 2};
    struct Item w = {.key = 3};
    struct Item y = {.key = 4};
    struct Item a = {.key = 5};
    struct Item b = {.key = 6};
    add(&pq, t);
    add(&pq, x);
    add(&pq, w);
    add(&pq, y);
    add(&pq, a);
    add(&pq, b);
    printQueue(&pq);
    struct Item e = extractMax(&pq);
    printf("e: %i\n", e.key);
    struct Item d = extractMax(&pq);
    printf("e: %i\n", d.key);
    struct Item f = extractMax(&pq);
    printf("e: %i\n", f.key);
    printQueue(&pq);
    freePriorityQueue(&pq);
    return 0;
}

void initializePriorityQueue(struct PriorityQueue *pq, int cap)
{
    struct Item *queue = malloc(sizeof(struct Item) * cap);
    (*pq) = (struct PriorityQueue){.queue = queue, .size = 0, .capacity = cap};
}

void printQueue(struct PriorityQueue *pq)
{
    for (int i = 0; i < (*pq).size; i++)
        printf("%i ", (*pq).queue[i].key);
    printf("\n");
}

void maxHeapifyBottomUp(struct PriorityQueue *pq, int index)
{
    if (index > (*pq).size)
        return;
    int father = index % 2 == 0 ? (index / 2) - 1 : index / 2;
    if (father < 0)
        return;
    if ((*pq).queue[index].key < (*pq).queue[father].key)
        return;

    struct Item temp = (*pq).queue[index];
    (*pq).queue[index] = (*pq).queue[father];
    (*pq).queue[father] = temp;

    maxHeapifyBottomUp(pq, father);
}

void maxHeapifyTopDown(struct PriorityQueue *pq, int index)
{
    if (index > (*pq).size)
        return;

    int max = index;
    int left = (index * 2) + 1;
    int right = (index * 2) + 2;

    if (left < (*pq).size && (*pq).queue[left].key > (*pq).queue[max].key)
    {
        max = left;
    }

    if (right < (*pq).size && (*pq).queue[right].key > (*pq).queue[left].key)
        max = right;

    if (max == index)
        return;

    struct Item temp = (*pq).queue[index];
    (*pq).queue[index] = (*pq).queue[max];
    (*pq).queue[max] = temp;
    maxHeapifyTopDown(pq, max);
}

void add(struct PriorityQueue *pq, struct Item item)
{
    if ((*pq).size >= (*pq).capacity)
        return;

    (*pq).queue[(*pq).size] = item;
    maxHeapifyBottomUp(pq, (*pq).size);
    (*pq).size++;
}

struct Item extractMax(struct PriorityQueue *pq)
{
    struct Item temp = (*pq).queue[0];
    (*pq).queue[0] = (*pq).queue[(*pq).size - 1];
    (*pq).queue[(*pq).size - 1] = temp;
    (*pq).size--;
    maxHeapifyTopDown(pq, 0);
    return temp;
}
void freePriorityQueue(struct PriorityQueue *pq)
{
    free((*pq).queue);
}
