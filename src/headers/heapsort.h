#ifndef HEAPSHORT_H
#define HEAPSHORT_H

/*void printArrayHeapSort(int *, int);
void heapSort(int *, int);
void heapSortDecrescent(int *, int);*/

void heapSort(void **, int, int (*comparator)(void *, void *));
void heapSortDecrescent(void **, int, int (*comparator)(void *, void *));
void printArrayHeapSort(void **, int, void (*printer)(void *));

#endif