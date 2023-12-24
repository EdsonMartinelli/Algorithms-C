#ifndef VECTOR_H
#define VECTOR_H
#define INIT_ARRAY_SIZE_VECTOR 16

typedef struct
{
    void **array;
    int nextElementIndex;
    int capacity;
} Vector;

void initializeVector(Vector *);
void pushBackVector(Vector *, void *);
void pushVectorWithIndex(Vector *, void *, int);
void expandVector(Vector *, int);
void *popVectorWithIndex(Vector *, int);
void freeVector(Vector *vec);

#endif