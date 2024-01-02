#include <stdlib.h>
#include "../../Unity/unity.h"
#include "../../../src/LinkedList/implementation/linkedlist.h"

LinkedList list;

void setUp()
{
    initLinkedList(&list);
}

void tearDown() {}

int main()
{
    UNITY_BEGIN();
    return UNITY_END();
}