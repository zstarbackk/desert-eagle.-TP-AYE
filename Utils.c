#include "Utils.h"

int TirarDado(void)
{
    int r;
    int limite = RAND_MAX - (RAND_MAX % 6);

    do
    {
        r = rand();
    } while (r >= limite);

    return (r % 6) + 1;
}
