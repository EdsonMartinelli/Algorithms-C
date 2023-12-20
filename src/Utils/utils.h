#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int randomIntNumber(int min, int max)
{
    srand(time(NULL));
    return (rand() % (max - min)) + min;
}

#endif
