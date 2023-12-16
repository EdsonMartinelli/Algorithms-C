#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node
{
    // int value;
    void *content;
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
LinkedListNode *pushInHead(LinkedList *, LinkedListNode *);
LinkedListNode *pushInTail(LinkedList *, LinkedListNode *);
LinkedListNode *pushInOrderCrescent(LinkedList *, LinkedListNode *, int (*comparator)(LinkedListNode *, LinkedListNode *));
LinkedListNode *pushInOrderDecrescent(LinkedList *, LinkedListNode *, int (*comparator)(LinkedListNode *, LinkedListNode *));
LinkedListNode *popFirst(LinkedList *);
LinkedListNode *popLast(LinkedList *);
LinkedListNode *popWithIndex(LinkedList *, int);
LinkedListNode *getFirst(LinkedList *);
LinkedListNode *getLast(LinkedList *);
LinkedListNode *getWithIndex(LinkedList *, int);
void printList(LinkedList list, void (*printer)(LinkedListNode));

#endif