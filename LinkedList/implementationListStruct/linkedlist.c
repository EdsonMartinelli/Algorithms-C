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

void pushInHead(LinkedListNode *item, LinkedList *list)
{
    item->next = (*list).head;
    if ((*list).tail == NULL)
        (*list).tail = item;
    (*list).head = item;
    (*list).size++;
}

void pushInTail(LinkedListNode *item, LinkedList *list)
{
    (*list).size++;
    if ((*list).tail == NULL)
    {
        (*list).tail = item;
        (*list).head = item;

        return;
    }
    LinkedListNode *temp = (*list).head;
    while ((*temp).next != NULL)
        temp = (*temp).next;
    (*temp).next = item;
    (*list).tail = item;
}

void pushInOrderCrescent(LinkedListNode *item, LinkedList *list)
{
    (*list).size++;
    if ((*list).head == NULL && (*list).tail == NULL)
    {
        (*list).tail = item;
        (*list).head = item;
        return;
    }

    LinkedListNode *ant = NULL;
    LinkedListNode *temp = (*list).head;
    while ((*temp).next != NULL && (*temp).value < (*item).value)
    {
        ant = temp;
        temp = (*temp).next;
    }

    if ((*temp).value < (*item).value)
    {
        (*temp).next = item;
        (*list).tail = item;
        return;
    }

    (*item).next = temp;
    if (ant == NULL)
    {
        (*list).head = item;
        return;
    }

    (*ant).next = item;
}

void pushInOrderDecrescent(LinkedListNode *item, LinkedList *list)
{
    (*list).size++;
    if ((*list).head == NULL && (*list).tail == NULL)
    {
        (*list).tail = item;
        (*list).head = item;
        return;
    }

    LinkedListNode *ant = NULL;
    LinkedListNode *temp = (*list).head;
    while ((*temp).next != NULL && (*temp).value > (*item).value)
    {
        ant = temp;
        temp = (*temp).next;
    }

    if ((*temp).value > (*item).value)
    {
        (*temp).next = item;
        (*list).tail = item;
        return;
    }

    (*item).next = temp;
    if (ant == NULL)
    {
        (*list).head = item;
        return;
    }

    (*ant).next = item;
}

void popFirst(LinkedList *list)
{
    if ((*list).head != NULL)
    {
        // LinkedListNode *newHead = (*(*list).head).next;
        (*list).head = (*(*list).head).next;
        (*list).size--;
    }
}

void popLast(LinkedList *list)
{
    LinkedListNode *ant = NULL;
    LinkedListNode *temp = (*list).head;

    if (temp == NULL)
        return;

    (*list).size--;
    while ((*temp).next != NULL)
    {
        ant = temp;
        temp = (*temp).next;
    }

    if (ant == NULL)
    {
        (*list).head = NULL;
        (*list).tail = NULL;
        return;
    }

    (*ant).next = NULL;
    (*list).tail = ant;
}

void popWithIndex(LinkedList *list, int index)
{
    LinkedListNode *ant = NULL;
    LinkedListNode *temp = (*list).head;

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

    (*list).size--;

    if ((*temp).next == NULL)
    {
        (*list).tail = ant;
    }

    if (ant == NULL)
    {
        (*list).head = (*temp).next;
        return;
    }
    (*ant).next = (*temp).next;
}

void printList(LinkedList list)
{
    LinkedListNode *temp = list.head;
    while (temp != NULL)
    {
        printf("%d \n", (*temp).value);
        temp = (*temp).next;
    }
}
