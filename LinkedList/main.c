#include <stdio.h>
#include "implementation/linkedlist.h"

int main()
{
    LinkedList list;
    initLinkedList(&list);

    LinkedListNode first = {.value = 10};
    LinkedListNode second = {.value = 12};
    LinkedListNode third = {.value = 22};
    LinkedListNode fourth = {.value = 7};
    LinkedListNode fifth = {.value = 1};

    pushInTail(&first, &list);
    pushInTail(&second, &list);
    pushInTail(&third, &list);
    pushInTail(&fourth, &list);
    pushInTail(&fifth, &list);
    /*pushInOrderCrescent(&first, &list);
    pushInOrderCrescent(&second, &list);
    pushInOrderCrescent(&third, &list);
    pushInOrderCrescent(&fourth, &list);
    pushInOrderCrescent(&fifth, &list);*/

    /*pushInOrderDecrescent(&first, &list);
    pushInOrderDecrescent(&second, &list);
    pushInOrderDecrescent(&third, &list);
    pushInOrderDecrescent(&fourth, &list);
    pushInOrderDecrescent(&fifth, &list);*/

    printf("size: %i \n", list.size);
    printf("Head value: %i \n", list.head == NULL ? -1 : list.head->value);
    printf("Tail value: %i \n", list.tail == NULL ? -1 : list.tail->value);
    printList(list);
    /* popFirst(&list);
     popFirst(&list);
     popFirst(&list);
     popFirst(&list);
     popFirst(&list);
     popFirst(&list);*/

    /*popLast(&list);
    popLast(&list);
    popLast(&list);
    popLast(&list);
    popLast(&list);
    popLast(&list);*/

    LinkedListNode *removedFirst = popWithIndex(&list, 0);
    printf("Removed Pointer Value: %i \n", removedFirst->value);
    LinkedListNode *removedSecond = popWithIndex(&list, 0);
    printf("Removed Pointer Value: %i \n", removedSecond->value);
    LinkedListNode *removedThird = popWithIndex(&list, 0);
    printf("Removed Pointer Value: %i \n", removedThird->value);
    /*popWithIndex(&list, 0);
    popWithIndex(&list, 0);*/

    printf("\nPopped List: \n");
    printf("size: %i \n", list.size);
    printf("Head value: %i \n", list.head == NULL ? -1 : list.head->value);
    printf("Tail value: %i \n", list.tail == NULL ? -1 : list.tail->value);
    printList(list);
    return 0;
}
