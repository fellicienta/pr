#include "lib.h"

#include <algorithm>
#include <random>

uint32_t experiment(const uint32_t quantity)
{
    uint32_t dice_roll();
    uint32_t frequency[13] = {};

    for (uint32_t i = 0; i < quantity; ++i)
        ++frequency[dice_roll() + dice_roll()];

    return std::distance(frequency, std::max_element(frequency + 2, frequency + 12));
}

uint32_t dice_roll()
{
    static std::random_device rd;
    static std::mt19937 g(rd());

    return rd() % 6 + 1;
}

uint32_t computation()
{
    double probability[13] = {};

    for (uint32_t i = 1; i <= 6; ++i)
        for (uint32_t j = 1; j <= 6; ++j)
            ++probability[i + j];

    uint32_t sum = 0;

    for (uint32_t i = 2; i <= 12; ++i)
        sum += probability[i];

    for (uint32_t i = 2; i <= 12; ++i)
        probability[i] /= sum;

    return std::distance(probability, std::max_element(probability + 2, probability + 12));
}