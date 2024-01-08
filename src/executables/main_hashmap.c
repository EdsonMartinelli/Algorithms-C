#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/hashmap.h"

int main()
{
    HashMap x;
    initHashMap(&x);
    int values[] = {15, 5, 25, 45, 100, 77, 12};
    int *test1 = (int *)addHashMap(&x, "teste", &values[0]);
    addHashMap(&x, "morte", &values[1]);
    addHashMap(&x, "dor", &values[2]);
    addHashMap(&x, "sofrimento", &values[3]);
    addHashMap(&x, "sofrimentosdfaasdfasdfasdfsadfsadfsvvsdfasdfsadfsdfa", &values[4]);
    int *test2 = (int *)addHashMap(&x, "teste", &values[5]);
    addHashMap(&x, "a", &values[6]);

    printf("Get Value for \"teste\": %i\n", *((int *)getHashMap(&x, "teste")));
    printf("Get Value for \"morte\": %i\n", *((int *)getHashMap(&x, "morte")));
    printf("Get Value for \"a\": %i\n", *((int *)getHashMap(&x, "a")));
    printf("Get Value for \"dor\": %i\n", *((int *)getHashMap(&x, "dor")));
    destroyHashMap(&x);
    return 0;
}