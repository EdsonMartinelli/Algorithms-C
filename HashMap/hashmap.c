#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../LinkedList/implementation/linkedlist.h"

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

void initializeHashMap(HashMap *hm)
{
    LinkedList *array = malloc(sizeof(LinkedList) * 16);
    memset(array, 0, 16);
    (*hm) = (HashMap){.array = array, .size = 0, .capacity = 16};
}

int hashFuncion(HashMap *hm, char *word)
{
    int hash = 0;
    int p = 31;
    for (int i = 0; i < strlen(word); i++)
        hash = p * hash + word[i];
    hash = hash % (*hm).capacity;
    int result = hash < 0 ? hash + (*hm).capacity : hash;
    printf("Hash for %s is: %i \n", word, result);
    return result;
}

LinkedListNode *addHashMap(HashMap *hm, char *key, int value)
{
    LinkedListNode *item = malloc(sizeof(LinkedListNode));
    HashItem *info = malloc(sizeof(HashItem));
    *info = (HashItem){.key = key, .value = value};
    item->content = info;
    int location = hashFuncion(hm, key);
    if (hm->array[location].head != NULL)
    {
        printf("COLLISION\n");
        pushInTail(&(hm->array[location]), item);
        return item;
    }

    initLinkedList(&(hm->array[location]));
    pushInTail(&(hm->array[location]), item);
    hm->size++;
    return item;
}

HashItem *getHashMap(HashMap *hm, char *key)
{
    int location = hashFuncion(hm, key);
    LinkedListNode *item = (hm->array[location].head);
    while (item != NULL)
    {
        printf("Key Value: %s\n", ((HashItem *)(item->content))->key);
        if (strcmp(((HashItem *)(item->content))->key, key) == 0)
            return (HashItem *)item->content;

        item = (*item).next;
    }

    return NULL;
}

void freeItem(LinkedListNode *item)
{
    HashItem *x = item->content;
    free(x);
    free(item);
}

int main()
{
    HashMap x;
    initializeHashMap(&x);
    LinkedListNode *i = addHashMap(&x, "teste", 15);
    LinkedListNode *y = addHashMap(&x, "morte", 5);
    LinkedListNode *u = addHashMap(&x, "dor", 25);
    LinkedListNode *k = addHashMap(&x, "sofrimento", 45);
    LinkedListNode *o = addHashMap(&x, "sofrimentosdfaasdfasdfasdfsadfsadfsvvsdfasdfsadfsdfa", 100);
    for (int i = 0; i < 16; i++)
    {
        if (x.array[i].head == NULL)
            printf("NULL \n");
        else
            printf("%i\n", ((HashItem *)(*x.array[i].head).content)->value);
    }
    printf("Get Value: %i\n", (*getHashMap(&x, "dor")).value);
    freeItem(i);
    freeItem(y);
    freeItem(u);
    freeItem(k);
    freeItem(o);
    free(x.array);
    return 0;
}