#ifndef HASHMAP_H
#define HASHMAP_H

#include "../../LinkedList/implementation/linkedlist.h"

#define INIT_ARRAY_SIZE 16

typedef struct
{
    char *key;
    int value;
} HashItem;

typedef struct
{
    LinkedList *array;
    int size;
    int capacity;
} HashMap;

void initializeHashMap(HashMap *);
LinkedListNode *addHashMap(HashMap *, char *, int);
HashItem *getHashMap(HashMap *, char *);
void freeHashMap(HashMap *);

#endif