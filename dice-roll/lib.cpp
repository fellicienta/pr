#include "lib.h"

#include <algorithm>
#include <map>
#include <random>

uint32_t experiment(const uint32_t dice, const uint32_t faces, const uint32_t experiments)
{
    uint32_t dice_roll(const uint32_t faces);
    std::map<uint32_t, uint32_t> frequency;

    for (uint32_t i = 0; i < experiments; ++i)
    {
        uint32_t sum = 0;
        for (uint32_t j = 0; j < dice; ++j)
            sum += dice_roll(faces);

        ++frequency[sum];
    }

    return (std::max_element(
                frequency.begin(), frequency.end(),
                [](const std::pair<uint32_t, uint32_t> &p1,
                   const std::pair<uint32_t, uint32_t> &p2) { return p1.second < p2.second; }))
        ->first;
}

uint32_t dice_roll(const uint32_t faces)
{
    static std::random_device rd;
    static std::mt19937 g(rd());

    return rd() % faces + 1;
}

// works for 2 dices only
uint32_t computation(const uint32_t faces)
{
    std::map<uint32_t, double> probability;

    for (uint32_t i = 1; i <= faces; ++i)
        for (uint32_t j = 1; j <= faces; ++j)
            ++probability[i + j];

    uint32_t sum = 0;

    for (auto x : probability)
        sum += x.second;

    for (auto x : probability)
        x.second /= sum;

    return (std::max_element(
                probability.begin(), probability.end(),
                [](const std::pair<uint32_t, uint32_t> &p1,
                   const std::pair<uint32_t, uint32_t> &p2) { return p1.second < p2.second; }))
        ->first;
}
