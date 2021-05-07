#include "lib.h"

#include <algorithm>
#include <map>
#include <random>

using Frequencies = std::map<uint32_t, uint32_t>;
using Frequency = Frequencies::const_iterator;

uint32_t roll_sample(const uint32_t dice_in_roll, const uint32_t die_faces,
                     const uint32_t sample_size)
{
    uint32_t roll_dice(const uint32_t dice_in_roll, const uint32_t die_faces);
    uint32_t find_highest_frequency(const Frequencies frequencies);
    Frequencies frequencies;

    for (uint32_t i = 0; i < sample_size; ++i)
        ++frequencies[roll_dice(dice_in_roll, die_faces)];

    return find_highest_frequency(frequencies);
}

uint32_t roll_dice(const uint32_t dice_in_roll, const uint32_t die_faces)
{
    static std::random_device rd;
    static std::mt19937 g(rd());

    uint32_t sum = 0;
    for (uint32_t i = 0; i < dice_in_roll; ++i)
        sum += rd() % die_faces + 1;

    return sum;
}

uint32_t find_highest_frequency(const Frequencies frequencies)
{
    Frequency it = std::max_element(
        frequencies.begin(), frequencies.end(),
        [](const std::pair<uint32_t, uint32_t> &p1, const std::pair<uint32_t, uint32_t> &p2) {
            return p1.second < p2.second;
        });

    return it->first;
}

// works for 2 dices only
// uint32_t computation(const uint32_t die_faces)
// {
//     std::map<uint32_t, double> probability;

//     for (uint32_t i = 1; i <= die_faces; ++i)
//         for (uint32_t j = 1; j <= die_faces; ++j)
//             ++probability[i + j];

//     uint32_t sum = 0;

//     for (auto x : probability)
//         sum += x.second;

//     for (auto x : probability)
//         x.second /= sum;

//     return (std::max_element(
//                 probability.begin(), probability.end(),
//                 [](const std::pair<uint32_t, uint32_t> &p1,
//                    const std::pair<uint32_t, uint32_t> &p2) { return p1.second < p2.second; }))
//         ->first;
// }
