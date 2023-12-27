#ifndef VECTOR_H
#define VECTOR_H
#define INIT_ARRAY_SIZE_VECTOR 16

typedef struct
{
    void **array;
    int size;
    int capacity;
} Vector;

void initializeVector(Vector *);
void pushBackVector(Vector *, void *);
void *popBackVector(Vector *);
void insertVector(Vector *, void *, int);
void insertNVector(Vector *vec, void *item, int quant, int index);
void insertArrayVector(Vector *vec, void **items, int firstIndex, int lastIndex, int index);
void erase(Vector *vec, int firstIndex, int lastIndex);
void freeVector(Vector *vec);

#endif