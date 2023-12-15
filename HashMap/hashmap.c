#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../LinkedList/implementation/linkedlist.h"
;

typedef struct
{
    LinkedList **array;
    int size;
    int capacity;
} HashMap;

void initializeHashMap(HashMap *hm)
{
    LinkedList **array = malloc(sizeof(LinkedList *) * 16);
    /* for (int i = 0; i < 16; i++)
         array[i] = NULL;*/
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
    item->value = value;
    int location = hashFuncion(hm, key);
    if (hm->array[location] != NULL)
    {
        printf("COLLISION\n");
        pushInTail(item, hm->array[location]);
        return item;
    }

    hm->array[location] = malloc(sizeof(LinkedList));
    initLinkedList(hm->array[location]);
    pushInTail(item, hm->array[location]);
    hm->size++;
    return item;
}

LinkedListNode *getHashMap(HashMap *hm, char *key)
{
    int location = hashFuncion(hm, key);
    if (hm->array[location] == NULL)
        return NULL;
    return hm->array[location]->head;
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
        if (x.array[i] == NULL)
            printf("NULL \n");
        else
            printf("%i\n", (*(*x.array[i]).head).value);
    }
    printf("Get Value: %i\n", (*getHashMap(&x, "teste")).value);
    free(i);
    free(y);
    free(u);
    free(k);
    free(o);
    for (int i = 0; i < x.capacity; i++)
        free(x.array[i]);
    free(x.array);
    return 0;
}