#include <stdlib.h>
#include "../Unity/unity.h"
#include "../../src/headers/hashmap.h"
#include "../../src/Utils/utils.h"

HashMap map;

void setUp()
{
    initHashMap(&map);
}

void tearDown()
{
    destroyHashMap(&map);
}

void hashmapShouldBeInitializedCorrectly()
{
    TEST_ASSERT_EQUAL(INIT_HASHMAP_SIZE, map.capacity);
    TEST_ASSERT_EQUAL(0, map.size);
    TEST_ASSERT_NOT_NULL(map.array);
}

void hashmapShouldAddItemAndGetCorrectValue()
{
    int testValue1 = 5;
    int testValue2 = 15;
    int *test1 = (int *)addHashMap(&map, "test", &testValue1);
    int *test2 = (int *)addHashMap(&map, "test2", &testValue2);

    TEST_ASSERT_NOT_NULL(test1);
    TEST_ASSERT_NOT_NULL(test2);

    int *getItem1 = (int *)getHashMap(&map, "test");
    int *getItem2 = (int *)getHashMap(&map, "test2");

    TEST_ASSERT_EQUAL_PTR(&testValue1, getItem1);
    TEST_ASSERT_EQUAL_PTR(&testValue2, getItem2);

    TEST_ASSERT_EQUAL(testValue1, *getItem1);
    TEST_ASSERT_EQUAL(testValue2, *getItem2);
}

void hashmapShouldReplaceValueIfItemHasAUsedKey()
{
    int testValue1 = 5;
    int testValue2 = 15;
    int *test1 = (int *)addHashMap(&map, "test", &testValue1);
    int *test2 = (int *)addHashMap(&map, "test", &testValue2);

    TEST_ASSERT_NOT_NULL(test1);
    TEST_ASSERT_NOT_NULL(test2);

    int *getItem = (int *)getHashMap(&map, "test");

    TEST_ASSERT_EQUAL_PTR(&testValue2, getItem);
    TEST_ASSERT_EQUAL(testValue2, *getItem);
}

void hashmapShouldReturnNullIfKeyDoesNotExist()
{
    TEST_ASSERT_NULL(getHashMap(&map, "test"));
}

void hashmapShouldRemoveItemCorrectly()
{
    int testValue = 5;
    int *item = (int *)addHashMap(&map, "test", &testValue);
    TEST_ASSERT_EQUAL(1, map.size);

    int *itemPopped = (int *)removeHashMap(&map, "test");

    TEST_ASSERT_NOT_NULL(item);
    TEST_ASSERT_NOT_NULL(itemPopped);
    TEST_ASSERT_EQUAL_PTR(item, itemPopped);
    TEST_ASSERT_EQUAL(0, map.size);
    TEST_ASSERT_NULL(getHashMap(&map, "test"));
}

void hashmapRemoveItemShouldReturnNullIfItemDoesNotExist()
{
    void *itemPopped = removeHashMap(&map, "test");
    TEST_ASSERT_NULL(itemPopped);
}

void printer(LinkedListNode item)
{
    printf("Key: %s Value: %d;  ", ((HashItem *)item.content)->key, *((int *)((HashItem *)item.content)->value));
}

void hashmapShouldIncreaseCapacityWhenItHitsLoadFactorAndGetCorrecValue()
{
    int n = (INIT_HASHMAP_SIZE * LOAD_FACTOR_HASHMAP) + 1;
    char keys[n][2];
    int values[n];

    for (int i = 0; i < n; i++)
    {
        keys[i][0] = (char)(97 + i);
        keys[i][1] = '\0';
        values[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        int *item = (int *)addHashMap(&map, keys[i], values + i);
        TEST_ASSERT_NOT_NULL(item);
    }

    TEST_ASSERT_EQUAL(INIT_HASHMAP_SIZE * 2, map.capacity);

    for (int i = 0; i < n; i++)
    {
        int *getItem = (int *)getHashMap(&map, keys[i]);
        TEST_ASSERT_EQUAL_PTR(values + i, getItem);
        TEST_ASSERT_EQUAL(values[i], *getItem);
    }
}

void hashmapShouldDecreaseCapacityWhenItHitsComplementLoadFactorAndGetCorrecValue()
{
    int n = (INIT_HASHMAP_SIZE * LOAD_FACTOR_HASHMAP) + 1;
    char keys[n][2];
    int values[n];

    for (int i = 0; i < n; i++)
    {
        keys[i][0] = (char)(97 + i);
        keys[i][1] = '\0';
        values[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        int *item = (int *)addHashMap(&map, keys[i], values + i);
        TEST_ASSERT_NOT_NULL(item);
    }

    TEST_ASSERT_EQUAL(INIT_HASHMAP_SIZE * 2, map.capacity);
    TEST_ASSERT_EQUAL(n, map.size);

    int nRemove = n - ((INIT_HASHMAP_SIZE * 2) * (1.0 - LOAD_FACTOR_HASHMAP)) + 1;
    for (int i = 0; i < nRemove; i++)
    {
        int *item = (int *)removeHashMap(&map, keys[i]);
        TEST_ASSERT_NOT_NULL(item);
    }

    TEST_ASSERT_EQUAL(n - nRemove, map.size);
    TEST_ASSERT_EQUAL(INIT_HASHMAP_SIZE, map.capacity);

    for (int i = nRemove; i < n; i++)
    {
        int *getItem = (int *)getHashMap(&map, keys[i]);
        TEST_ASSERT_EQUAL_PTR(values + i, getItem);
        TEST_ASSERT_EQUAL(values[i], *getItem);
    }
}

void hashmapShouldRemoveTheCorrectItemAfterExpand()
{
    int n = INIT_HASHMAP_SIZE;
    char keys[n][2];
    int values[n];

    for (int i = 0; i < n; i++)
    {
        keys[i][0] = (char)(97 + i);
        keys[i][1] = '\0';
        values[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        int *item = (int *)addHashMap(&map, keys[i], values + i);
        TEST_ASSERT_NOT_NULL(item);
    }

    TEST_ASSERT_EQUAL(INIT_HASHMAP_SIZE * 2, map.capacity);

    int index = randomIntNumber(0, n, 0);
    int *getItem = (int *)getHashMap(&map, keys[index]);
    int *itemPopped = (int *)removeHashMap(&map, keys[index]);

    TEST_ASSERT_NOT_NULL(itemPopped);
    TEST_ASSERT_NULL(getHashMap(&map, keys[index]));
    TEST_ASSERT_EQUAL_PTR(getItem, itemPopped);
    TEST_ASSERT_EQUAL(*getItem, *itemPopped);
}

void hashmapShouldRemoveTheCorrectItemAfterExpandAndShrink()
{
    int n = INIT_HASHMAP_SIZE;
    char keys[n][2];
    int values[n];

    for (int i = 0; i < n; i++)
    {
        keys[i][0] = (char)(97 + i);
        keys[i][1] = '\0';
        values[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        int *item = (int *)addHashMap(&map, keys[i], values + i);
        TEST_ASSERT_NOT_NULL(item);
    }

    TEST_ASSERT_EQUAL(n, map.size);
    TEST_ASSERT_EQUAL(INIT_HASHMAP_SIZE * 2, map.capacity);

    int nRemove = n - ((INIT_HASHMAP_SIZE * 2) * (1.0 - LOAD_FACTOR_HASHMAP)) + 1;
    for (int i = 0; i < nRemove; i++)
    {
        int *item = (int *)removeHashMap(&map, keys[i]);
        TEST_ASSERT_NOT_NULL(item);
    }

    TEST_ASSERT_EQUAL(n - nRemove, map.size);
    TEST_ASSERT_EQUAL(INIT_HASHMAP_SIZE, map.capacity);

    int index = randomIntNumber(nRemove, n, 0);
    int *getItem = (int *)getHashMap(&map, keys[index]);
    int *itemPopped = (int *)removeHashMap(&map, keys[index]);

    TEST_ASSERT_NOT_NULL(itemPopped);
    TEST_ASSERT_NULL(getHashMap(&map, keys[index]));
    TEST_ASSERT_EQUAL_PTR(getItem, itemPopped);
    TEST_ASSERT_EQUAL(*getItem, *itemPopped);
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
    RUN_TEST(hashmapShouldIncreaseCapacityWhenItHitsLoadFactorAndGetCorrecValue);
    RUN_TEST(hashmapShouldDecreaseCapacityWhenItHitsComplementLoadFactorAndGetCorrecValue);
    RUN_TEST(hashmapShouldRemoveTheCorrectItemAfterExpand);
    RUN_TEST(hashmapShouldRemoveTheCorrectItemAfterExpandAndShrink);
    return UNITY_END();
}