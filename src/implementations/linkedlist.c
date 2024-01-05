#include <stdio.h>
#include "../headers/linkedlist.h"

void initLinkedList(LinkedList *list)
{
    *list = (LinkedList){.head = NULL, .tail = NULL, .size = 0};
}

LinkedListNode *pushInHead(LinkedList *list, LinkedListNode *item)
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

LinkedListNode *pushInTail(LinkedList *list, LinkedListNode *item)
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

LinkedListNode *pushInOrderCrescent(
    LinkedList *list,
    LinkedListNode *item,
    int (*comparator)(LinkedListNode *a, LinkedListNode *b))
{
    (*item).previous = NULL;
    (*item).next = NULL;

    if ((*list).size == 0)
        return pushInHead(list, item);

    LinkedListNode *temp = (*list).head;

    while ((*temp).next != NULL && (*comparator)(temp, item) <= 0)
        temp = (*temp).next;

    if ((*comparator)(temp, item) > 0)
    {
        if ((*temp).previous == NULL)
            return pushInHead(list, item);

        (*(*temp).previous).next = item;

        (*item).previous = (*temp).previous;
        (*item).next = temp;

        (*temp).previous = item;

        (*list).size++;
        return item;
    }

    return pushInTail(list, item);
}

LinkedListNode *pushInOrderDecrescent(
    LinkedList *list,
    LinkedListNode *item,
    int (*comparator)(LinkedListNode *a, LinkedListNode *b))
{
    (*item).previous = NULL;
    (*item).next = NULL;

    if ((*list).size == 0)
        return pushInHead(list, item);

    LinkedListNode *temp = (*list).head;

    while ((*temp).next != NULL && (*comparator)(temp, item) >= 0)
        temp = (*temp).next;

    if ((*comparator)(temp, item) < 0)
    {
        if ((*temp).previous == NULL)
            return pushInHead(list, item);

        (*(*temp).previous).next = item;

        (*item).previous = (*temp).previous;
        (*item).next = temp;

        (*temp).previous = item;

        (*list).size++;
        return item;
    }

    return pushInTail(list, item);
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
    if (index > (*list).size - 1 || index < 0)
        return NULL;

    LinkedListNode *temp = (*list).head;

    while ((*temp).next != NULL && index > 0)
    {
        temp = (*temp).next;
        index--;
    }

    if ((*temp).next == NULL)
        return popLast(list);

    if ((*temp).previous == NULL)
        return popFirst(list);

    (*(*temp).next).previous = (*temp).previous;
    (*(*temp).previous).next = (*temp).next;
    (*list).size--;
    return temp;
}

LinkedListNode *popWithAddress(LinkedList *list, LinkedListNode *item)
{
    LinkedListNode *temp = (*list).head;
    while (temp != NULL)
    {
        if (item == temp)
            break;
        temp = temp->next;
    }

    if (temp == NULL)
        return NULL;

    if (item->next != NULL)
        (item->next)->previous = item->previous;
    else
        list->tail = item->previous;

    if (item->previous != NULL)
        (item->previous)->next = item->next;
    else
        list->head = item->next;

    list->size--;
    return item;
}

LinkedListNode *getFirst(LinkedList *list)
{
    return (*list).head;
}

LinkedListNode *getLast(LinkedList *list)
{
    return (*list).tail;
}

LinkedListNode *getWithIndex(LinkedList *list, int index)
{
    if (index < 0)
        return NULL;

    LinkedListNode *temp = (*list).head;

    if (temp == NULL)
        return NULL;

    while ((*temp).next != NULL && index > 0)
    {
        temp = (*temp).next;
        index--;
    }

    if (index > 0)
        return NULL;

    return temp;
}

bool isLinkedListEmpty(LinkedList list)
{
    if (list.size == 0 && list.head == NULL && list.tail == NULL)
        return true;
    return false;
}

void printList(LinkedList list, void (*printer)(LinkedListNode item))
{
    LinkedListNode *temp = list.head;
    if (temp == NULL)
        printf("Empty List\n");
    while (temp != NULL)
    {
        (*printer)(*temp);
        temp = (*temp).next;
    }
}
