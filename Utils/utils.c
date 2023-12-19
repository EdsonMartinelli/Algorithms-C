#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

union teste
{
    int keyInt;
    char *keyString;
};

int main()
{
    union teste x;
    x.keyString = "teste";
    printf("%i\n", randomIntNumber(10, 20));
    printf("%s\n", x.keyString);
    return 0;
}
