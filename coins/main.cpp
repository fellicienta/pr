#include "coins.h"
#include <iostream>
#include <random>

int main()
{
    const uint16_t required = 11;
    const uint16_t quantity = 1000;
    uint32_t average = 0;

    for (uint16_t i = 0; i < quantity; ++i)
    {
        average += play(required);
    }

    average /= quantity;
    std::cout << "Average : " << average << std::endl;

    return 0;
}
