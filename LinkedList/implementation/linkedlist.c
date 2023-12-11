#include <stdio.h>
#include "linkedlist.h"

LinkedListNode createLinkedListNode(int value)
{
    LinkedListNode new = {.value = value, .next = NULL};
    return new;
}

void initLinkedList(LinkedList *list)
{
    *list = (LinkedList){.head = NULL, .tail = NULL, .size = 0};
}

void pushInTail(LinkedListNode *item, LinkedListNode **list)
{
    if (*list == NULL)
    {
        *list = item;
        return;
    }

    LinkedListNode *temp = *list;
    while ((*temp).next != NULL)
        temp = (*temp).next;
    (*temp).next = item;
}

void pushInHead(LinkedListNode *item, LinkedListNode **list)
{
    item->next = *list;
    *list = item;
}

void pushInOrderCrescent(LinkedListNode *item, LinkedListNode **list)
{
    if (*list == NULL)
    {
        *list = item;
        return;
    }

    LinkedListNode *ant = NULL;
    LinkedListNode *temp = *list;
    while ((*temp).next != NULL && (*temp).value < (*item).value)
    {
        ant = temp;
        temp = (*temp).next;
    }

    if ((*temp).value < (*item).value)
    {
        (*temp).next = item;
        return;
    }

    (*item).next = temp;
    if (ant == NULL)
    {
        *list = item;
        return;
    }

    (*ant).next = item;
}

void pushInOrderDecrescent(LinkedListNode *item, LinkedListNode **list)
{
    if (*list == NULL)
    {
        *list = item;
        return;
    }

    LinkedListNode *ant = NULL;
    LinkedListNode *temp = *list;
    while ((*temp).next != NULL && (*temp).value > (*item).value)
    {
        ant = temp;
        temp = (*temp).next;
    }

    if ((*temp).value > (*item).value)
    {
        (*temp).next = item;
        return;
    }

    (*item).next = temp;
    if (ant == NULL)
    {
        *list = item;
        return;
    }

    (*ant).next = item;
}

void popFirst(LinkedListNode **list)
{
    if (*list != NULL)
    {
        LinkedListNode *newHead = (**list).next;
        *list = newHead;
    }
}

void popLast(LinkedListNode **list)
{
    LinkedListNode *ant = NULL;
    LinkedListNode *temp = *list;

    if (temp == NULL)
        return;

    while ((*temp).next != NULL)
    {
        ant = temp;
        temp = (*temp).next;
    }

    if (ant == NULL)
    {
        *list = NULL;
        return;
    }

    (*ant).next = NULL;
}

void popWithIndex(LinkedListNode **list, int index)
{
    LinkedListNode *ant = NULL;
    LinkedListNode *temp = *list;

    if (temp == NULL)
        return;

    while ((*temp).next != NULL && index > 0)
    {
        ant = temp;
        temp = (*temp).next;
        index--;
    }

    if (index > 0)
        return;

    if (ant == NULL)
    {
        *list = (*temp).next;
        return;
    }
    (*ant).next = (*temp).next;
}

void printList(LinkedListNode *list)
{
    while (list != NULL)
    {
        printf("%d \n", (*list).value);
        list = (*list).next;
    }
}
