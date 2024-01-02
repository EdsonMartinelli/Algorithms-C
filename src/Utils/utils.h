#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int randomIntNumber(int min, int max, int seedLoop)
{
    srand(time(0) + seedLoop);
    return (rand() % (max - min)) + min;
}

#endif
