#ifndef HASHMAP_H
#define HASHMAP_H

#include "linkedlist.h"

#define INIT_HASHMAP_SIZE 16
#define LOAD_FACTOR_HASHMAP 0.75

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

void initHashMap(HashMap *);
HashItem *addHashMap(HashMap *, char *, int);
HashItem *getHashMap(HashMap *, char *);
HashItem *removeHashMap(HashMap *, char *);
void destroyHashMap(HashMap *);

#endif