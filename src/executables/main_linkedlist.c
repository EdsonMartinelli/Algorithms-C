#include <stdio.h>
#include "../headers/linkedlist.h"

typedef struct
{
    int value;
} Thing;

void printer(LinkedListNode item)
{

    Thing *c = (Thing *)item.content;

    if (c == NULL)
    {
        printf("Error");
    }

    printf("Value: %d; ", (*c).value);
    printf("Previous: %i; ", item.previous == NULL ? -1 : ((Thing *)(*item.previous).content)->value);
    printf("Next: %i \n", item.next == NULL ? -1 : ((Thing *)item.next->content)->value);
}

int comparator(LinkedListNode *a, LinkedListNode *b)
{
    return ((Thing *)a->content)->value - ((Thing *)b->content)->value;
}

int main()
{
    int values[] = {10, 12, 22, 7, 1};
    Thing things[5];
    for (int i = 0; i < 5; i++)
        things[i] = (Thing){.value = values[i]};

    LinkedList list;
    initLinkedList(&list);

    LinkedListNode first = {.content = &things[0]};
    LinkedListNode second = {.content = &things[1]};
    LinkedListNode third = {.content = &things[2]};
    LinkedListNode fourth = {.content = &things[3]};
    LinkedListNode fifth = {.content = &things[4]};

    /*pushInTail(&list, &first);
    pushInTail(&list, &second);
    pushInTail(&list, &third);
    pushInTail(&list, &fourth);
    pushInTail(&list, &fifth);*/

    /*pushInHead(&list, &first);
    pushInHead(&list, &second);
    pushInHead(&list, &third);
    pushInHead(&list, &fourth);
    pushInHead(&list, &fifth);*/

    pushInOrderCrescent(&list, &first, &comparator);
    pushInOrderCrescent(&list, &second, &comparator);
    pushInOrderCrescent(&list, &third, &comparator);
    pushInOrderCrescent(&list, &fourth, &comparator);
    pushInOrderCrescent(&list, &fifth, &comparator);

    /*pushInOrderDecrescent(&list, &first, &comparator);
    pushInOrderDecrescent(&list, &second, &comparator);
    pushInOrderDecrescent(&list, &third, &comparator);
    pushInOrderDecrescent(&list, &fourth, &comparator);
    pushInOrderDecrescent(&list, &fifth, &comparator);*/

    // popWithAddress(&list, &fifth);

    printf("size: %i \n", list.size);
    printf("Head value: %i \n", list.head == NULL ? -1 : ((Thing *)list.head->content)->value);
    printf("Tail value: %i \n", list.tail == NULL ? -1 : ((Thing *)list.tail->content)->value);
    printList(list, &printer);
    printf("Value of Second item: %i\n", ((Thing *)getWithIndex(&list, 1)->content)->value);
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

    /* LinkedListNode *removedFirst = popWithIndex(&list, 0);
     printf("Removed Pointer Value: %i \n", ((Thing *)removedFirst->content)->value);
     LinkedListNode *removedSecond = popWithIndex(&list, 0);
     printf("Removed Pointer Value: %i \n", ((Thing *)removedSecond->content)->value);
     LinkedListNode *removedThird = popWithIndex(&list, 0);
     printf("Removed Pointer Value: %i \n", ((Thing *)removedThird->content)->value);*/
    /*popWithIndex(&list, 0);
    popWithIndex(&list, 0);*/

    /*printf("\nPopped List: \n");
    printf("size: %i \n", list.size);
    printf("Head value: %i \n", list.head == NULL ? -1 : ((Thing *)list.head->content)->value);
    printf("Tail value: %i \n", list.tail == NULL ? -1 : ((Thing *)list.tail->content)->value);
    printList(list, &printer);*/
    return 0;
}
