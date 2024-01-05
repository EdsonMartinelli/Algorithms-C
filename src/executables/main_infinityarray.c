#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/infinityarray.h"

int main()
{
    InfinityArray vec;
    initInfinityArray(&vec);
    int a = 1;
    int b = 2;
    int c = 10;
    pushInfinityArray(&vec, &a);
    pushInfinityArray(&vec, &b);

    pushInfinityArray(&vec, &a);
    pushInfinityArray(&vec, &b);

    pushInfinityArray(&vec, &a);
    pushInfinityArray(&vec, &b);

    setInfinityArray(&vec, &c, 4);
    setInfinityArray(&vec, &c, 9);

    popInfinityArray(&vec);
    popInfinityArray(&vec);
    popInfinityArray(&vec);
    popInfinityArray(&vec);
    popInfinityArray(&vec);
    popInfinityArray(&vec);
    popInfinityArray(&vec);

    for (int i = 0; i < lengthInfinityArray(vec); i++)
    {
        if (vec.array[i] == NULL)
            printf("NULL\n");
        else
            printf("%i\n", *((int *)vec.array[i]));
    }

    destroyInfinityArray(&vec);
    return 0;
}