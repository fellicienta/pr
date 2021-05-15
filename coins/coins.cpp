#include "coins.h"

#include <random>
#include <stdint.h>

uint16_t flip_a_coin()
{
    static std::random_device rd;
    static std::mt19937 g(rd());

    return rd() % 2;
}

uint16_t play(const uint16_t required)
{
    uint16_t counter = 1;
    uint32_t fling;
    uint16_t previous_value = flip_a_coin();
    uint32_t current_value;

    for (fling = 2; required != counter; ++fling)
    {
        current_value = flip_a_coin();

        if (current_value == previous_value)
        {
            ++counter;
        }
        else
        {
            counter = 1;
            previous_value = current_value;
        }
    }

    return fling;
}