#include <stdio.h>
#include "linkedlist.h"

void initLinkedList(LinkedList *list)
{
    *list = (LinkedList){.head = NULL, .tail = NULL, .size = 0};
}

LinkedListNode *pushInHead(LinkedListNode *item, LinkedList *list)
{
    (*item).previous = NULL;
    item->next = (*list).head;

    if ((*list).head != NULL)
        (*(*list).head).previous = item;

    if ((*list).size == 0 && (*list).tail == NULL)
        (*list).tail = item;

    (*list).head = item;
    (*list).size++;
    return item;
}

LinkedListNode *pushInTail(LinkedListNode *item, LinkedList *list)
{
    (*item).next = NULL;
    (*item).previous = (*list).tail;

    if ((*list).tail != NULL)
        (*(*list).tail).next = item;

    if ((*list).size == 0 && (*list).head == NULL)
        (*list).head = item;

    (*list).tail = item;
    (*list).size++;
    return item;
}

LinkedListNode *pushInOrderCrescent(LinkedListNode *item, LinkedList *list)
{
    (*item).previous = NULL;
    (*item).next = NULL;

    if ((*list).size == 0)
        return pushInHead(item, list);

    LinkedListNode *temp = (*list).head;

    while ((*temp).next != NULL && (*temp).value <= (*item).value)
        temp = (*temp).next;

    if ((*temp).next == NULL)
        return pushInTail(item, list);

    if ((*temp).previous == NULL)
        return pushInHead(item, list);

    (*(*temp).previous).next = item;

    (*item).previous = (*temp).previous;
    (*item).next = temp;

    (*temp).previous = item;

    (*list).size++;
    return item;
}

LinkedListNode *pushInOrderDecrescent(LinkedListNode *item, LinkedList *list)
{
    (*item).previous = NULL;
    (*item).next = NULL;

    if ((*list).size == 0)
        return pushInHead(item, list);

    LinkedListNode *temp = (*list).head;

    while ((*temp).next != NULL && (*temp).value >= (*item).value)
        temp = (*temp).next;

    if ((*temp).next == NULL)
        return pushInTail(item, list);

    if ((*temp).previous == NULL)
        return pushInHead(item, list);

    (*(*temp).previous).next = item;

    (*item).previous = (*temp).previous;
    (*item).next = temp;

    (*temp).previous = item;

    (*list).size++;
    return item;
}

LinkedListNode *popFirst(LinkedList *list)
{
    if ((*list).size == 0 && (*list).head == NULL)
        return NULL;

    LinkedListNode *p = (*list).head;
    (*list).head = (*(*list).head).next;

    if ((*list).head != NULL)
        (*(*list).head).previous = NULL;
    else
        (*list).tail = NULL;

    (*list).size--;
    return p;
}

LinkedListNode *popLast(LinkedList *list)
{
    if ((*list).size == 0 && (*list).tail == NULL)
        return NULL;

    LinkedListNode *p = (*list).tail;
    (*list).tail = (*(*list).tail).previous;

    if ((*list).tail != NULL)
        (*(*list).tail).next = NULL;
    else
        (*list).head = NULL;

    (*list).size--;
    return p;
}

LinkedListNode *popWithIndex(LinkedList *list, int index)
{
    if ((*list).size == 0)
        return NULL;

    LinkedListNode *temp = (*list).head;

    while ((*temp).next != NULL && index > 0)
    {
        temp = (*temp).next;
        index--;
    }

    if (index > 0)
        return NULL;

    if ((*temp).next == NULL)
        return popLast(list);

    if ((*temp).previous == NULL)
        return popFirst(list);

    (*(*temp).next).previous = (*temp).previous;
    (*(*temp).previous).next = (*temp).next;
    (*list).size--;
    return temp;
}

void printList(LinkedList list)
{
    LinkedListNode *temp = list.head;
    if (temp == NULL)
        printf("Empty List\n");
    while (temp != NULL)
    {
        printf("Value: %d; Previous: %i; Next: %i \n", (*temp).value, (*temp).previous == NULL ? -1 : (*(*temp).previous).value, (*temp).next == NULL ? -1 : (*(*temp).next).value);
        temp = (*temp).next;
    }
}
