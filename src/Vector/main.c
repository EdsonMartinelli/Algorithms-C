#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "implementation/vector.h"

int main()
{
    void **x = (void **)malloc(sizeof(void *) * 5);
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
    x[0] = &c;
    x[1] = &c;
    x[2] = &c;
    x[3] = &c;
    x[4] = &c;
    // pushVectorWithIndex(&vec, &c, 4);

    // pushVectorWithIndex(&vec, &c, 9);

    // popVectorWithIndex(&vec, 16);

    /*popBackVector(&vec);
    popBackVector(&vec);
    popBackVector(&vec);
    popBackVector(&vec);*/
    // insertVector(&vec, &c, 1);
    // insertNVector(&vec, &c, 2, 6);
    // insertArrayVector(&vec, x, 0, 2, 1);
    // erase(&vec, 1, 6);

    resizeVector(&vec, 20, &c);

    /*printf("Cap: %i\n", vec.capacity);
    shrinkToFitVector(&vec);
    printf("Cap: %i\n", vec.capacity);*/

    for (int i = 0; i < vec.size; i++)
    {
        if (vec.array[i] == NULL)
            printf("NULL\n");
        else
            printf("%i\n", *((int *)atVector(vec, i)));
    }
    free(x);
    freeVector(&vec);
    return 0;
}