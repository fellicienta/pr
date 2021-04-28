#include "lib.h"

#include <random>
#include <stdint.h>

uint32_t baby()
{
    static std::random_device rd;
    static std::mt19937 g(rd());

    return rd() % 2;
}

double get_ratio()
{
    uint32_t families = 100000;
    uint32_t girls = 0;

    for (uint32_t i = 0; i < families; ++i)
    {
        while (baby() != 1)
            ++girls;
    }

    return (double)families / girls;
}
