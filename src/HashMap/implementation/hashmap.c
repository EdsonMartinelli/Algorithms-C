#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

void initializeHashMap(HashMap *hm)
{
    LinkedList *array = malloc(sizeof(LinkedList) * INIT_ARRAY_SIZE);
    memset(array, 0, INIT_ARRAY_SIZE);
    (*hm) = (HashMap){.array = array, .size = 0, .capacity = INIT_ARRAY_SIZE};
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
        LinkedListNode *temp = (hm->array[location].head);
        while (temp != NULL)
        {
            if (strcmp(((HashItem *)(temp->content))->key, key) == 0)
            {
                printf("Key already used: Replacing data;\n");
                free(item);
                free(temp->content);
                temp->content = info;
                return temp;
            }
            temp = (*temp).next;
        }
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
        // printf("Key Value: %s\n", ((HashItem *)(item->content))->key);
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
