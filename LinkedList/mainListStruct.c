#include <stdio.h>
#include "implementationListStruct/linkedlist.h"

int main()
{
    LinkedList list;
    initLinkedList(&list);

    LinkedListNode first = createLinkedListNode(10);
    LinkedListNode second = createLinkedListNode(12);
    LinkedListNode third = createLinkedListNode(22);
    LinkedListNode fourth = createLinkedListNode(7);
    LinkedListNode fifth = createLinkedListNode(1);

    pushInHead(&first, &list);
    pushInHead(&second, &list);
    pushInHead(&third, &list);
    pushInHead(&fourth, &list);
    pushInHead(&fifth, &list);
    /* pushInOrderCrescent(&first, &list);
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
    printf("Head value: %i \n", list.head->value);
    printf("Tail value: %i \n", list.tail->value);
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

    // popWithIndex(&list, 0);

    /*printf("\nPopped List: \n");
    printf("size: %i \n", list.size);
    printf("Head value: %i \n", list.head->value);
    printf("Tail value: %i \n", list.tail->value);
    printList(list);*/
    return 0;
}
