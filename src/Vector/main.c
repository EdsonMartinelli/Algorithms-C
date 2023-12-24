#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "implementation/vector.h"

int main()
{
    Vector vec;
    initializeVector(&vec);
    int a = 1;
    int b = 2;
    int c = 10;
    pushBackVector(&vec, &a);
    pushBackVector(&vec, &b);

    pushBackVector(&vec, &a);
    pushBackVector(&vec, &b);

    pushBackVector(&vec, &a);
    pushBackVector(&vec, &b);

    pushVectorWithIndex(&vec, &c, 4);

    pushVectorWithIndex(&vec, &c, 9);

    // popVectorWithIndex(&vec, 16);

    for (int i = 0; i < vec.capacity; i++)
    {
        if (vec.array[i] == NULL)
            printf("NULL\n");
        else
            printf("%i\n", *((int *)vec.array[i]));
    }

    freeVector(&vec);
    return 0;
}