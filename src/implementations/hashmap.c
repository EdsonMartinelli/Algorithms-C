#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/hashmap.h"

void initHashMap(HashMap *hm)
{
    LinkedList *array = (LinkedList *)malloc(sizeof(LinkedList) * INIT_HASHMAP_SIZE);
    if (array == NULL)
    {
        fprintf(stderr, "[ERROR] Memory Allocate Failure.");
        exit(EXIT_FAILURE);
    }
    // memset(array, 0, sizeof(LinkedList) * INIT_HASHMAP_SIZE);
    for (int i = 0; i < INIT_HASHMAP_SIZE; i++)
        initLinkedList(&array[i]);

    (*hm) = (HashMap){.array = array, .size = 0, .capacity = INIT_HASHMAP_SIZE};
}

static int hashFuncion(HashMap *hm, char *word)
{
    int hash = 0;
    int p = 31;
    for (int i = 0; i < strlen(word); i++)
        hash = p * hash + word[i];
    hash = hash % (*hm).capacity;
    int result = hash < 0 ? hash + (*hm).capacity : hash;
    return result;
}

static void reallocateData(HashMap *hm, int begin, int end)
{
    for (int location = begin; location < end; location++)
    {
        LinkedListNode *temp = hm->array[location].head;
        while (temp != NULL)
        {
            LinkedListNode *nextNode = temp->next;
            int newLocation = hashFuncion(hm, ((HashItem *)temp->content)->key);
            if (location != newLocation)
            {
                LinkedListNode *poppedItem = popWithAddress(&hm->array[location], temp);
                pushInTail(&hm->array[newLocation], poppedItem);
            }
            temp = nextNode;
        }
    }
}

static void expandArray(HashMap *hm)
{
    LinkedList *newArray = realloc(hm->array, sizeof(LinkedList) * hm->capacity * 2);
    if (newArray == NULL)
    {
        fprintf(stderr, "[ERROR] Memory Allocate Failure.");
        exit(EXIT_FAILURE);
    }
    for (int i = hm->capacity; i < hm->capacity * 2; i++)
        initLinkedList(&newArray[i]);
    hm->array = newArray;
    hm->capacity = hm->capacity * 2;
    reallocateData(hm, 0, hm->capacity / 2);
}

static void shrinkArray(HashMap *hm)
{
    if (hm->capacity <= INIT_HASHMAP_SIZE)
        return;
    int oldCapacity = hm->capacity;
    hm->capacity = hm->capacity / 2;
    reallocateData(hm, hm->capacity, oldCapacity);

    LinkedList *newArray = realloc(hm->array, sizeof(LinkedList) * hm->capacity);
    if (newArray == NULL)
    {
        fprintf(stderr, "[ERROR] Memory Allocate Failure.");
        exit(EXIT_FAILURE);
    }
    hm->array = newArray;
}

static void verifyLoad(HashMap *hm)
{
    float loadFactor = 0.75;
    float currentLoad = hm->size / (float)hm->capacity;

    if (currentLoad >= LOAD_FACTOR_HASHMAP)
        expandArray(hm);

    if (currentLoad <= 1.0 - LOAD_FACTOR_HASHMAP)
        shrinkArray(hm);
}

void *addHashMap(HashMap *hm, char *key, void *value)
{
    HashItem *info = (HashItem *)malloc(sizeof(HashItem));
    if (info == NULL)
    {
        fprintf(stderr, "[ERROR] Memory Allocate Failure.");
        exit(EXIT_FAILURE);
    }
    *info = (HashItem){.key = key, .value = value};
    int location = hashFuncion(hm, key);

    if (isLinkedListEmpty(hm->array[location]))
        hm->size++;

    LinkedListNode *temp = hm->array[location].head;

    while (temp != NULL)
    {
        if (strcmp(((HashItem *)(temp->content))->key, key) == 0)
        {
            free(temp->content);
            temp->content = info;
            return info->value;
        }
        temp = (*temp).next;
    }
    LinkedListNode *item = malloc(sizeof(LinkedListNode));
    if (item == NULL)
    {
        fprintf(stderr, "[ERROR] Memory Allocate Failure.");
        exit(EXIT_FAILURE);
    }
    item->content = info;
    pushInTail(&(hm->array[location]), item);
    verifyLoad(hm);
    return info->value;
}

void *getHashMap(HashMap *hm, char *key)
{
    int location = hashFuncion(hm, key);
    LinkedListNode *item = (hm->array[location].head);
    while (item != NULL)
    {
        if (strcmp(((HashItem *)(item->content))->key, key) == 0)
            return ((HashItem *)item->content)->value;
        item = (*item).next;
    }
    return NULL;
}

void *removeHashMap(HashMap *hm, char *key)
{
    int location = hashFuncion(hm, key);
    LinkedListNode *item = (hm->array[location].head);
    while (item != NULL)
    {
        if (strcmp(((HashItem *)(item->content))->key, key) == 0)
        {
            LinkedListNode *itemPopped = popWithAddress(&(hm->array[location]), item);
            if (isLinkedListEmpty(hm->array[location]))
            {
                hm->size--;
                verifyLoad(hm);
            }
            return ((HashItem *)itemPopped->content)->value;
        }
        item = (*item).next;
    }
    return NULL;
}

void destroyHashMap(HashMap *hm)
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
