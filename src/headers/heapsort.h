#ifndef HEAPSHORT_H
#define HEAPSHORT_H

void heapSort(void **, int, int (*comparator)(void *, void *));
void heapSortDecrescent(void **, int, int (*comparator)(void *, void *));
void printArrayHeapSort(void **, int, void (*printer)(void *));

#endif