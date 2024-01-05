#include <stdlib.h>
#include "../../Unity/unity.h"
#include "../../../src/headers/hashmap.h"
#include "../../../src/Utils/utils.h"

HashMap map;

void setUp()
{
    initializeHashMap(&map);
}

void tearDown()
{
    freeHashMap(&map);
}

void hashmapShouldBeInitializedCorrectly()
{
    TEST_ASSERT_EQUAL(INIT_HASHMAP_SIZE, map.capacity);
    TEST_ASSERT_EQUAL(0, map.size);
    TEST_ASSERT_NOT_NULL(map.array);
}

void hashmapShouldAddItemAndGetCorrectValue()
{
    HashItem *test1 = addHashMap(&map, "test", 5);
    HashItem *test2 = addHashMap(&map, "test2", 15);

    TEST_ASSERT_NOT_NULL(test1);
    TEST_ASSERT_NOT_NULL(test2);

    TEST_ASSERT_EQUAL(5, (*getHashMap(&map, "test")).value);
    TEST_ASSERT_EQUAL(15, (*getHashMap(&map, "test2")).value);
}

void hashmapShouldReplaceValueIfItemHasAUsedKey()
{
    HashItem *test1 = addHashMap(&map, "test", 5);
    HashItem *test2 = addHashMap(&map, "test", 15);

    TEST_ASSERT_NOT_NULL(test1);
    TEST_ASSERT_NOT_NULL(test2);

    TEST_ASSERT_EQUAL(15, (*getHashMap(&map, "test")).value);
}

void hashmapShouldReturnNullIfKeyDoesNotExist()
{
    TEST_ASSERT_NULL(getHashMap(&map, "test"));
}

void hashmapShouldRemoveItemCorrectly()
{
    HashItem *item = addHashMap(&map, "test", 5);
    HashItem *itemPopped = removeHashMap(&map, "test");

    TEST_ASSERT_NOT_NULL(item);
    TEST_ASSERT_NOT_NULL(itemPopped);
    TEST_ASSERT_EQUAL_PTR(item, itemPopped);
    TEST_ASSERT_NULL(getHashMap(&map, "test"));
}

void hashmapRemoveItemShouldReturnNullIfItemDoesNotExist()
{
    HashItem *itemPopped = removeHashMap(&map, "test");
    TEST_ASSERT_NULL(itemPopped);
}

void printer(LinkedListNode node)
{
    printf("Key:%s; Value:%i - ", (*((HashItem *)node.content)).key, (*((HashItem *)node.content)).value);
}

void hashmapShouldIncreaseCapacityWhenItIsAlmostFullAndGetCorrecValue()
{
    int n = INIT_HASHMAP_SIZE;
    char word[n][2];

    for (int i = 0; i < n; i++)
    {
        word[i][0] = (char)(97 + i);
        word[i][1] = '\0';
    }

    for (int i = 0; i < n; i++)
    {
        HashItem *item = addHashMap(&map, word[i], i);
        TEST_ASSERT_NOT_NULL(item);
    }

    TEST_ASSERT_EQUAL(INIT_HASHMAP_SIZE * 2, map.capacity);

    for (int i = 0; i < n; i++)
    {
        TEST_ASSERT_EQUAL(i, (*getHashMap(&map, word[i])).value);
    }
}

void hashmapShouldRemoveTheCorrectItemAfterExpand()
{
    int n = INIT_HASHMAP_SIZE;
    char word[n][2];

    for (int i = 0; i < n; i++)
    {
        word[i][0] = (char)(97 + i);
        word[i][1] = '\0';
    }

    for (int i = 0; i < n; i++)
    {
        HashItem *item = addHashMap(&map, word[i], i);
        TEST_ASSERT_NOT_NULL(item);
    }

    TEST_ASSERT_EQUAL(INIT_HASHMAP_SIZE * 2, map.capacity);

    int index = randomIntNumber(0, n, 0);
    HashItem *itemPopped = removeHashMap(&map, word[index]);

    TEST_ASSERT_NOT_NULL(itemPopped);
    TEST_ASSERT_NULL(getHashMap(&map, word[index]));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(hashmapShouldBeInitializedCorrectly);
    RUN_TEST(hashmapShouldAddItemAndGetCorrectValue);
    RUN_TEST(hashmapShouldReplaceValueIfItemHasAUsedKey);
    RUN_TEST(hashmapShouldReturnNullIfKeyDoesNotExist);
    RUN_TEST(hashmapShouldRemoveItemCorrectly);
    RUN_TEST(hashmapRemoveItemShouldReturnNullIfItemDoesNotExist);
    RUN_TEST(hashmapShouldIncreaseCapacityWhenItIsAlmostFullAndGetCorrecValue);
    RUN_TEST(hashmapShouldRemoveTheCorrectItemAfterExpand);
    return UNITY_END();
}