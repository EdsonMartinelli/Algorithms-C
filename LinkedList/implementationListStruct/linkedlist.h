#ifndef LINKEDLIST2_H
#define LINKEDLIST2_H

typedef struct Node
{
    int value;
    struct Node *next;
} LinkedListNode;

typedef struct
{
    LinkedListNode *head;
    LinkedListNode *tail;
    int size;
} LinkedList;

void initLinkedList(LinkedList *list);
LinkedListNode createLinkedListNode(int);
void pushInHead(LinkedListNode *, LinkedList *);
void pushInTail(LinkedListNode *, LinkedList *);
void pushInOrderCrescent(LinkedListNode *, LinkedList *);
void pushInOrderDecrescent(LinkedListNode *, LinkedList *);
void popFirst(LinkedList *);
void popLast(LinkedList *);
void popWithIndex(LinkedList *, int);
void printList(LinkedList list);

#endif /* LINKEDLIST2_H */