#include <stdlib.h>
#include "../../Unity/unity.h"
#include "../../../src/headers/hashmap.h"
#include "../../../src/Utils/utils.h"

#define expSize 10

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

int main()
{
    UNITY_BEGIN();
    RUN_TEST(hashmapShouldBeInitializedCorrectly);
    RUN_TEST(hashmapShouldAddItemAndGetCorrectValue);
    RUN_TEST(hashmapShouldReplaceValueIfItemHasAUsedKey);
    RUN_TEST(hashmapShouldReturnNullIfKeyDoesNotExist);
    return UNITY_END();
}