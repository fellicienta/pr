#include "lib.h"

#include <random>
#include <stdint.h>

uint32_t baby()
{
    static std::random_device rd;
    static std::mt19937 g(rd());

    return rd() % 2;
}

double get_ratio1()
{
    uint32_t families = 100000;
    double ratio;

    for (uint32_t i = 0; i < families; ++i)
    {
        uint32_t sex[2] = {0, 0};

        while (sex[1] != 1)
            ++sex[baby()];

        ratio += (double)sex[0] / sex[1];
    }

    return ratio / families;
}

double get_ratio2()
{
    uint32_t families = 100000;
    uint32_t girls = 0;
    uint32_t boys = 0;

    for (uint32_t i = 0; i < families; ++i)
    {
        while (baby() != 1)
            ++girls;
    }

    return (double)families / girls;
}