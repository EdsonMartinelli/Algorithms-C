#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "implementation/hashmap.h"

int main()
{
    HashMap x;
    initializeHashMap(&x);
    LinkedListNode *i = addHashMap(&x, "teste", 15);
    addHashMap(&x, "morte", 5);
    addHashMap(&x, "dor", 25);
    addHashMap(&x, "sofrimento", 45);
    addHashMap(&x, "sofrimentosdfaasdfasdfasdfsadfsadfsvvsdfasdfsadfsdfa", 100);
    LinkedListNode *test = addHashMap(&x, "teste", 77);
    addHashMap(&x, "a", 12);
    for (int i = 0; i < INIT_ARRAY_SIZE; i++)
    {
        if (x.array[i].head == NULL)
            printf("NULL \n");
        else
            printf("%i\n", ((HashItem *)(*x.array[i].head).content)->value);
    }
    printf("Get Value for \"teste\": %i\n", (*getHashMap(&x, "teste")).value);
    printf("Get Value for \"morte\": %i\n", (*getHashMap(&x, "morte")).value);
    printf("Get Value for \"a\": %i\n", (*getHashMap(&x, "a")).value);
    printf("%p %p\n", i, test);
    freeHashMap(&x);
    return 0;
}