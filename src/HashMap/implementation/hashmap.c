#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

#define INIT_ARRAY_SIZE 2

// PRIVATE FUNCTIONS
int hashFuncion(HashMap *, char *);
void verifyLoad(HashMap *);
void expandArray(HashMap *);
void reallocateData(HashMap *);

void initializeHashMap(HashMap *hm)
{
    LinkedList *array = (LinkedList *)malloc(sizeof(LinkedList) * INIT_ARRAY_SIZE);
    if (array == NULL)
    {
        printf("Memory Allocate Failure.");
        exit(EXIT_FAILURE);
    }
    // memset(array, 0, sizeof(LinkedList) * INIT_ARRAY_SIZE);
    for (int i = 0; i < INIT_ARRAY_SIZE; i++)
        initLinkedList(&array[i]);
    (*hm) = (HashMap){.array = array, .size = 0, .capacity = INIT_ARRAY_SIZE};
}

void reallocateData(HashMap *hm)
{
    for (int location = 0; location < hm->capacity / 2; location++)
    {
        LinkedListNode *temp = hm->array[location].head;
        while (temp != NULL)
        {
            LinkedListNode *nextNode = temp->next;
            int newLocation = hashFuncion(hm, ((HashItem *)temp->content)->key);
            if (location != newLocation)
            {
                printf("Change Node Location (%s) from %i to %i\n", ((HashItem *)temp->content)->key, location, newLocation);
                LinkedListNode *poppedItem = popWithAddress(&hm->array[location], temp);
                pushInTail(&hm->array[newLocation], poppedItem);
            }
            temp = nextNode;
        }
    }
}

void expandArray(HashMap *hm)
{
    LinkedList *newArray = realloc(hm->array, sizeof(LinkedList) * hm->capacity * 2);
    if (newArray == NULL)
    {
        printf("Memory Allocate Failure.");
        exit(EXIT_FAILURE);
    }
    for (int i = hm->capacity; i < hm->capacity * 2; i++)
        initLinkedList(&newArray[i]);
    hm->array = newArray;
    hm->capacity = hm->capacity * 2;
    reallocateData(hm);
}

void verifyLoad(HashMap *hm)
{
    float loadFactor = 0.75;
    float currentLoad = hm->size / (float)hm->capacity;

    if (currentLoad >= loadFactor)
    {
        printf("Size: %i; ", hm->size);
        printf("Capacity: %i; ", hm->capacity);
        printf("Expanding Array...\n");
        expandArray(hm);
    }
}

int hashFuncion(HashMap *hm, char *word)
{
    int hash = 0;
    int p = 31;
    for (int i = 0; i < strlen(word); i++)
        hash = p * hash + word[i];
    hash = hash % (*hm).capacity;
    int result = hash < 0 ? hash + (*hm).capacity : hash;
    return result;
}

HashItem *addHashMap(HashMap *hm, char *key, int value)
{

    HashItem *info = (HashItem *)malloc(sizeof(HashItem));
    if (info == NULL)
    {
        printf("Memory Allocate Failure.");
        exit(EXIT_FAILURE);
    }
    *info = (HashItem){.key = key, .value = value};
    int location = hashFuncion(hm, key);

    printf("Key: %s; Data: %i; Location: %i; ", key, value, location);
    if (hm->array[location].head == NULL)
        hm->size++;

    if (hm->array[location].head != NULL)
        printf("COLLISION: ");

    LinkedListNode *temp = (hm->array[location].head);
    while (temp != NULL)
    {
        if (strcmp(((HashItem *)(temp->content))->key, key) == 0)
        {
            printf("Key already used (%s) - Replacing data\n", key);
            free(temp->content);
            temp->content = info;
            return info;
        }
        temp = (*temp).next;
    }

    if (hm->array[location].head != NULL)
        printf("New Key (%s) - Adding data", key);

    LinkedListNode *item = malloc(sizeof(LinkedListNode));
    if (item == NULL)
    {
        printf("Memory Allocate Failure.");
        exit(EXIT_FAILURE);
    }
    item->content = info;
    pushInTail(&(hm->array[location]), item);
    printf("\n");
    verifyLoad(hm);
    return info;
}

HashItem *getHashMap(HashMap *hm, char *key)
{
    int location = hashFuncion(hm, key);
    LinkedListNode *item = (hm->array[location].head);
    while (item != NULL)
    {
        if (strcmp(((HashItem *)(item->content))->key, key) == 0)
            return (HashItem *)item->content;

        item = (*item).next;
    }

    return NULL;
}

void freeHashMap(HashMap *hm)
{
    for (int i = 0; i < hm->capacity; i++)
        while (hm->array[i].head != NULL)
        {
            LinkedListNode *item = popLast(&hm->array[i]);
            HashItem *info = item->content;
            free(info);
            free(item);
        }
    free(hm->array);
}
