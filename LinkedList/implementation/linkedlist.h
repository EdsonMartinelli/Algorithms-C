#ifndef LINKEDLIST_H
#define LINKEDLIST_H

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

LinkedListNode createLinkedListNode(int);
void pushInTail(LinkedListNode *, LinkedListNode **);
void pushInHead(LinkedListNode *, LinkedListNode **);
void pushInOrderCrescent(LinkedListNode *, LinkedListNode **);
void pushInOrderDecrescent(LinkedListNode *, LinkedListNode **);
void popFirst(LinkedListNode **);
void popLast(LinkedListNode **);
void popWithIndex(LinkedListNode **, int);
void printList(LinkedListNode *);

#endif /* LINKEDLIST_H */