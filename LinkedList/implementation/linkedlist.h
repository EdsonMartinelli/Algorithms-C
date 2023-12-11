#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node
{
    int value;
    struct Node *previous;
    struct Node *next;
} LinkedListNode;

typedef struct
{
    LinkedListNode *head;
    LinkedListNode *tail;
    int size;
} LinkedList;

void initLinkedList(LinkedList *list);
LinkedListNode *pushInHead(LinkedListNode *, LinkedList *);
LinkedListNode *pushInTail(LinkedListNode *, LinkedList *);
LinkedListNode *pushInOrderCrescent(LinkedListNode *, LinkedList *);
LinkedListNode *pushInOrderDecrescent(LinkedListNode *, LinkedList *);
LinkedListNode *popFirst(LinkedList *);
LinkedListNode *popLast(LinkedList *);
LinkedListNode *popWithIndex(LinkedList *, int);
void printList(LinkedList list);

#endif