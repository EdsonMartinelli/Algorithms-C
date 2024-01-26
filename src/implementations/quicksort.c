#include <stdio.h>
#include "../headers/quicksort.h"
#include "../utils/utils.h"

static void sort(
    void **array,
    int arrayStart,
    int arrayEnd,
    int (*comparator)(void *, void *))
{
    if (arrayStart >= arrayEnd)
        return;

    int index = randomIntNumber(arrayStart, arrayEnd, arrayEnd);

    void *temp = array[arrayEnd - 1];
    array[arrayEnd - 1] = array[index];
    array[index] = temp;

    int arrayMid = arrayStart;
    for (int i = arrayStart; i < arrayEnd - 1; i++)
    {
        int comp = (*comparator)(array[i], array[arrayEnd - 1]);

        if (comp < 0)
        {
            temp = array[arrayMid];
            array[arrayMid] = array[i];
            array[i] = temp;
            arrayMid++;
        }
    }

    temp = array[arrayMid];
    array[arrayMid] = array[arrayEnd - 1];
    array[arrayEnd - 1] = temp;

    sort(array, arrayStart, arrayMid, comparator);
    sort(array, arrayMid + 1, arrayEnd, comparator);
}

static void sortDecrescent(
    void **array,
    int arrayStart,
    int arrayEnd,
    int (*comparator)(void *, void *))
{
    if (arrayStart >= arrayEnd)
        return;

    int index = randomIntNumber(arrayStart, arrayEnd, arrayEnd);

    void *temp = array[arrayEnd - 1];
    array[arrayEnd - 1] = array[index];
    array[index] = temp;

    int arrayMid = arrayStart;
    for (int i = arrayStart; i < arrayEnd - 1; i++)
    {

        int comp = (*comparator)(array[i], array[arrayEnd - 1]);

        if (comp > 0)
        {

            temp = array[arrayMid];
            array[arrayMid] = array[i];
            array[i] = temp;
            arrayMid++;
        }
    }

    temp = array[arrayMid];
    array[arrayMid] = array[arrayEnd - 1];
    array[arrayEnd - 1] = temp;

    sortDecrescent(array, arrayStart, arrayMid, comparator);
    sortDecrescent(array, arrayMid + 1, arrayEnd, comparator);
}

void quickSort(void **array, int arraySize, int (*comparator)(void *, void *))
{
    sort(array, 0, arraySize, comparator);
}

void quickSortDecrescent(void **array, int arraySize, int (*comparator)(void *, void *))
{
    sortDecrescent(array, 0, arraySize, comparator);
}
