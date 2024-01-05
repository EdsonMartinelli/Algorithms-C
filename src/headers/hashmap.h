#ifndef HASHMAP_H
#define HASHMAP_H

#include "linkedlist.h"

#define INIT_HASHMAP_SIZE 2
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