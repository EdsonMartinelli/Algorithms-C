#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
    void **array;
    int size;
    int capacity;
} Vector;

void initializeVector(Vector *vec);
void pushBackVector(Vector *vec, void *item);
void *popBackVector(Vector *vec);
void insertVector(Vector *vec, void *item, int index);
void insertNVector(Vector *vec, void *item, int quant, int index);
void insertArrayVector(Vector *vec, void **items, int firstIndex, int lastIndex, int index);
void eraseVector(Vector *vec, int firstIndex, int lastIndex);
void swapVector(Vector *vec1, Vector *vec2);
void clearVector(Vector *vec);
void shrinkToFitVector(Vector *vec);
int IsEmptyVector(Vector *vec);
void *atVector(Vector *vec, int index);
void resizeVector(Vector *vec, int n, void *initItem);
void freeVector(Vector *vec);

#endif