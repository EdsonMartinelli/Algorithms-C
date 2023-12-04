#include <stdio.h>

struct Node
{
    int value;
    struct Node *next;
};

struct Node createNode(int);
void pushInTail(struct Node *, struct Node **);
void pushInHead(struct Node *, struct Node **);
void pushInOrderCrescent(struct Node *, struct Node **);
void pushInOrderDecrescent(struct Node *, struct Node **);
void popFirst(struct Node **);
void popLast(struct Node **);
void popWithIndex(struct Node **, int);
void printList(struct Node *);

int main()
{
    struct Node first = createNode(10);
    struct Node second = createNode(12);
    struct Node third = createNode(22);
    struct Node fourth = createNode(7);
    struct Node fifth = createNode(1);
    struct Node *list = NULL;

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

struct Node createNode(int value)
{
    struct Node new = {.value = value, .next = NULL};
    return new;
}

void pushInTail(struct Node *item, struct Node **list)
{
    if (*list == NULL)
    {
        *list = item;
        return;
    }

    struct Node *temp = *list;
    while ((*temp).next != NULL)
        temp = (*temp).next;
    (*temp).next = item;
}

void pushInHead(struct Node *item, struct Node **list)
{
    item->next = *list;
    *list = item;
}

void pushInOrderCrescent(struct Node *item, struct Node **list)
{
    if (*list == NULL)
    {
        *list = item;
        return;
    }

    struct Node *ant = NULL;
    struct Node *temp = *list;
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

void pushInOrderDecrescent(struct Node *item, struct Node **list)
{
    if (*list == NULL)
    {
        *list = item;
        return;
    }

    struct Node *ant = NULL;
    struct Node *temp = *list;
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

void popFirst(struct Node **list)
{
    if (*list != NULL)
    {
        struct Node *newHead = (**list).next;
        *list = newHead;
    }
}

void popLast(struct Node **list)
{
    struct Node *ant = NULL;
    struct Node *temp = *list;

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

void popWithIndex(struct Node **list, int index)
{
    struct Node *ant = NULL;
    struct Node *temp = *list;

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

void printList(struct Node *list)
{
    while (list != NULL)
    {
        printf("%d \n", (*list).value);
        list = (*list).next;
    }
}
