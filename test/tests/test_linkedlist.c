#include <stdlib.h>
#include "../Unity/unity.h"
#include "../../src/headers/linkedlist.h"
#include "../../src/utils/utils.h"

#define expSize 5

LinkedList list;

int values[expSize];
LinkedListNode nodes[expSize];

void setUp()
{
    initLinkedList(&list);
    for (int i = 0; i < expSize; i++)
    {
        values[i] = randomIntNumber(-100, 100, i);
        nodes[i] = (LinkedListNode){.content = &values[i]};
    }
}

void tearDown() {}

static int comparator(LinkedListNode *a, LinkedListNode *b)
{
    return *((int *)a->content) - *((int *)b->content);
}

void linkedListShouldPushNodeInTail()
{
    for (int i = 0; i < expSize; i++)
        pushInTail(&list, &nodes[i]);

    TEST_ASSERT_EQUAL(expSize, list.size);
    TEST_ASSERT_EQUAL_PTR(&nodes[expSize - 1], list.tail);

    LinkedListNode *temp = list.head;
    for (int i = 0; i < expSize; i++)
    {
        TEST_ASSERT_EQUAL(*((int *)temp->content), values[i]);
        temp = temp->next;
    }
}

void linkedListShouldPushNodeInHead()
{
    for (int i = 0; i < expSize; i++)
        pushInHead(&list, &nodes[i]);

    TEST_ASSERT_EQUAL(expSize, list.size);
    TEST_ASSERT_EQUAL_PTR(&nodes[expSize - 1], list.head);

    LinkedListNode *temp = list.head;
    for (int i = 0; i < expSize; i++)
    {
        TEST_ASSERT_EQUAL(*((int *)temp->content), values[expSize - 1 - i]);
        temp = temp->next;
    }
}

void linkedListShouldPushNodeInCrescentOrder()
{
    for (int i = 0; i < expSize; i++)
        pushInOrderCrescent(&list, &nodes[i], &comparator);

    TEST_ASSERT_EQUAL(expSize, list.size);

    LinkedListNode *temp = list.head;
    for (int i = 0; i < expSize; i++)
    {
        if (temp->next != NULL)
        {
            /*if (*((int *)temp->content) > *((int *)(temp->next)->content))
                TEST_FAIL();*/
            TEST_ASSERT_GREATER_OR_EQUAL_INT32(*((int *)temp->content), *((int *)(temp->next)->content));
        }
        temp = temp->next;
    }
}

void linkedListShouldPushNodeInDecrescentOrder()
{
    for (int i = 0; i < expSize; i++)
        pushInOrderDecrescent(&list, &nodes[i], &comparator);

    TEST_ASSERT_EQUAL(expSize, list.size);

    LinkedListNode *temp = list.head;
    for (int i = 0; i < expSize; i++)
    {
        if (temp->next != NULL)
        {
            /*if (*((int *)temp->content) < *((int *)(temp->next)->content))
                TEST_FAIL();*/
            TEST_ASSERT_LESS_OR_EQUAL_INT32(*((int *)temp->content), *((int *)(temp->next)->content));
        }
        temp = temp->next;
    }
}

void linkedListShouldGetFirstNode()
{
    for (int i = 0; i < expSize; i++)
        pushInTail(&list, &nodes[i]);

    LinkedListNode *first = getFirst(&list);
    TEST_ASSERT_EQUAL(*((int *)first->content), values[0]);
}

void linkedListGetFirstShouldReturnNullIfListIsEmpty()
{
    LinkedListNode *first = getFirst(&list);
    TEST_ASSERT_EQUAL(0, list.size);
    TEST_ASSERT_NULL(first);
}

void linkedListShouldGetLastNode()
{
    for (int i = 0; i < expSize; i++)
        pushInTail(&list, &nodes[i]);

    LinkedListNode *last = getLast(&list);
    TEST_ASSERT_EQUAL(*((int *)last->content), values[expSize - 1]);
}

void linkedListGetLastShouldReturnNullIfListIsEmpty()
{
    LinkedListNode *last = getFirst(&list);
    TEST_ASSERT_EQUAL(0, list.size);
    TEST_ASSERT_NULL(last);
}

void linkedListShouldGetNodeWithIndex()
{
    int index = randomIntNumber(0, 5, 0);
    for (int i = 0; i < expSize; i++)
        pushInTail(&list, &nodes[i]);

    LinkedListNode *node = getWithIndex(&list, index);
    TEST_ASSERT_EQUAL(*((int *)node->content), values[index]);
}

void linkedListGetNodeWithIndexShouldReturnNullIfIndexDoesNotExist()
{
    for (int i = 0; i < expSize; i++)
        pushInTail(&list, &nodes[i]);

    LinkedListNode *node = getWithIndex(&list, -1);
    LinkedListNode *node2 = getWithIndex(&list, expSize + 1);
    TEST_ASSERT_EQUAL(expSize, list.size);
    TEST_ASSERT_NULL(node);
    TEST_ASSERT_NULL(node2);
}

void linkedListShouldPopFirstNode()
{
    for (int i = 0; i < expSize; i++)
        pushInTail(&list, &nodes[i]);

    LinkedListNode *first = getFirst(&list);
    LinkedListNode *firstPopped = popFirst(&list);

    TEST_ASSERT_EQUAL_PTR(first->next, list.head);

    TEST_ASSERT_EQUAL(*((int *)first->content), values[0]);

    TEST_ASSERT_EQUAL(expSize - 1, list.size);
    TEST_ASSERT_EQUAL_PTR(first, firstPopped);

    LinkedListNode *temp = list.head;
    for (int i = 0; i < expSize - 1; i++)
    {
        TEST_ASSERT_EQUAL(*((int *)temp->content), values[i + 1]);
        temp = temp->next;
    }
}

void linkedListPopFirstShouldReturnNullIfListIsEmpty()
{
    LinkedListNode *first = popFirst(&list);
    TEST_ASSERT_EQUAL(0, list.size);
    TEST_ASSERT_NULL(first);
}

void linkedListShouldPopLastNode()
{
    for (int i = 0; i < expSize; i++)
        pushInTail(&list, &nodes[i]);

    LinkedListNode *last = getLast(&list);
    LinkedListNode *lastPopped = popLast(&list);

    TEST_ASSERT_EQUAL_PTR(last->previous, list.tail);

    TEST_ASSERT_EQUAL(*((int *)last->content), values[expSize - 1]);

    TEST_ASSERT_EQUAL(expSize - 1, list.size);
    TEST_ASSERT_EQUAL_PTR(last, lastPopped);

    LinkedListNode *temp = list.head;
    for (int i = 0; i < expSize - 1; i++)
    {
        TEST_ASSERT_EQUAL(*((int *)temp->content), values[i]);
        temp = temp->next;
    }
}

void linkedListPopLastShouldReturnNullIfListIsEmpty()
{
    LinkedListNode *last = popLast(&list);
    TEST_ASSERT_EQUAL(0, list.size);
    TEST_ASSERT_NULL(last);
}

void linkedListShouldPopNodeWithIndex()
{
    int index = randomIntNumber(0, 5, 0);
    for (int i = 0; i < expSize; i++)
        pushInTail(&list, &nodes[i]);

    LinkedListNode *node = getWithIndex(&list, index);
    LinkedListNode *nodePopped = popWithIndex(&list, index);

    TEST_ASSERT_EQUAL(*((int *)nodePopped->content), values[index]);

    TEST_ASSERT_EQUAL(expSize - 1, list.size);
    TEST_ASSERT_EQUAL_PTR(node, nodePopped);

    LinkedListNode *temp = list.head;
    for (int i = 0; i < expSize - 1; i++)
    {
        TEST_ASSERT_EQUAL(*((int *)temp->content), values[i >= index ? i + 1 : i]);
        temp = temp->next;
    }
}

void linkedListPopWithIndexShouldReturnNullIfIndexDoesNotExist()
{

    for (int i = 0; i < expSize; i++)
        pushInTail(&list, &nodes[i]);

    LinkedListNode *node = popWithIndex(&list, -1);
    LinkedListNode *node2 = popWithIndex(&list, expSize + 1);
    TEST_ASSERT_EQUAL(expSize, list.size);
    TEST_ASSERT_NULL(node);
    TEST_ASSERT_NULL(node2);
}

void linkedListShouldPopNodeWithAddress()
{
    int index = randomIntNumber(0, 5, 0);
    for (int i = 0; i < expSize; i++)
        pushInTail(&list, &nodes[i]);

    LinkedListNode *node = getWithIndex(&list, index);
    LinkedListNode *nodePopped = popWithAddress(&list, node);
    TEST_ASSERT_EQUAL(*((int *)nodePopped->content), values[index]);

    TEST_ASSERT_EQUAL(expSize - 1, list.size);
    TEST_ASSERT_EQUAL_PTR(node, nodePopped);

    LinkedListNode *temp = list.head;
    for (int i = 0; i < expSize - 1; i++)
    {
        TEST_ASSERT_EQUAL(*((int *)temp->content), values[i >= index ? i + 1 : i]);
        temp = temp->next;
    }
}

void linkedListPopWithAddressShouldReturnNullIfNodeNotExistInList()
{
    int index = randomIntNumber(0, 5, 0);
    for (int i = 0; i < expSize; i++)
        pushInTail(&list, &nodes[i]);

    LinkedListNode invalidNode = (LinkedListNode){.content = &values[0]};
    LinkedListNode *node = &invalidNode;
    LinkedListNode *nodePopped = popWithAddress(&list, node);

    TEST_ASSERT_EQUAL(expSize, list.size);
    TEST_ASSERT_NULL(nodePopped);

    LinkedListNode *temp = list.head;
    for (int i = 0; i < expSize; i++)
    {
        TEST_ASSERT_EQUAL(*((int *)temp->content), values[i]);
        temp = temp->next;
    }
}

void linkedListShouldReturnTrueIfItIsEmpty()
{
    TEST_ASSERT_TRUE(isLinkedListEmpty(list));
    TEST_ASSERT_EQUAL(0, list.size);
}

void linkedListShouldReturnFalseIfItIsNotEmpty()
{
    for (int i = 0; i < expSize; i++)
        pushInTail(&list, &nodes[i]);

    TEST_ASSERT_FALSE(isLinkedListEmpty(list));
    TEST_ASSERT_EQUAL(expSize, list.size);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(linkedListShouldPushNodeInTail);
    RUN_TEST(linkedListShouldPushNodeInHead);
    RUN_TEST(linkedListShouldPushNodeInCrescentOrder);
    RUN_TEST(linkedListShouldPushNodeInDecrescentOrder);
    RUN_TEST(linkedListShouldGetFirstNode);
    RUN_TEST(linkedListGetFirstShouldReturnNullIfListIsEmpty);
    RUN_TEST(linkedListShouldGetLastNode);
    RUN_TEST(linkedListGetLastShouldReturnNullIfListIsEmpty);
    RUN_TEST(linkedListShouldGetNodeWithIndex);
    RUN_TEST(linkedListGetNodeWithIndexShouldReturnNullIfIndexDoesNotExist);
    RUN_TEST(linkedListShouldPopFirstNode);
    RUN_TEST(linkedListPopFirstShouldReturnNullIfListIsEmpty);
    RUN_TEST(linkedListShouldPopLastNode);
    RUN_TEST(linkedListPopLastShouldReturnNullIfListIsEmpty);
    RUN_TEST(linkedListShouldPopNodeWithIndex);
    RUN_TEST(linkedListPopWithIndexShouldReturnNullIfIndexDoesNotExist);
    RUN_TEST(linkedListShouldPopNodeWithAddress);
    RUN_TEST(linkedListPopWithAddressShouldReturnNullIfNodeNotExistInList);
    RUN_TEST(linkedListShouldReturnTrueIfItIsEmpty);
    RUN_TEST(linkedListShouldReturnFalseIfItIsNotEmpty);
    return UNITY_END();
}