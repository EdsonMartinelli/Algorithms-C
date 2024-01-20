#ifndef QUICKSORT_H
#define QUICKSORT_H

void quickSort(void **, int, int (*comparator)(void *, void *));
void quickSortDecrescent(void **, int, int (*comparator)(void *, void *));

#endif