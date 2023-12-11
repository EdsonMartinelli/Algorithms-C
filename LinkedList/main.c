#include <stdio.h>
#include "implementation/linkedlist.h"

int main()
{
    LinkedListNode first = createLinkedListNode(10);
    LinkedListNode second = createLinkedListNode(12);
    LinkedListNode third = createLinkedListNode(22);
    LinkedListNode fourth = createLinkedListNode(7);
    LinkedListNode fifth = createLinkedListNode(1);
    LinkedListNode *list = NULL;

    pushInHead(&first, &list);
    pushInHead(&second, &list);
    pushInHead(&third, &list);
    pushInHead(&fourth, &list);
    pushInHead(&fifth, &list);
    /*pushInOrderCrescent(&first, &list);
    pushInOrderCrescent(&fourth, &list);
    pushInOrderCrescent(&second, &list);
    pushInOrderCrescent(&third, &list);
    pushInOrderCrescent(&fifth, &list);*/

    /*pushInOrderDecrescent(&first, &list);
    pushInOrderDecrescent(&fourth, &list);
    pushInOrderDecrescent(&second, &list);
    pushInOrderDecrescent(&third, &list);
    pushInOrderDecrescent(&fifth, &list);*/

    printList(list);
    /*popFirst(&list);
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

    /*popWithIndex(&list, 3);*/

    /*printf("Popped List: \n");
    printList(list);*/
    return 0;
}
