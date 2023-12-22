#ifndef HASHMAP_H
#define HASHMAP_H

#include "../../LinkedList/implementation/linkedlist.h"

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
HashItem *addHashMap(HashMap *, char *, int);
HashItem *getHashMap(HashMap *, char *);
void freeHashMap(HashMap *);

#endif