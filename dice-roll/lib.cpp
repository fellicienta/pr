#include "lib.h"

#include <algorithm>
#include <map>
#include <random>

using Value = uint32_t;
using Frequencies = std::map<Value, uint32_t>;
using Frequency = Frequencies::const_iterator;

namespace
{
uint32_t roll_dice(const uint32_t dice_in_roll, const uint32_t die_faces)
{
    static std::random_device rd;
    static std::mt19937 g(rd());

    uint32_t sum = 0;
    for (uint32_t i = 0; i < dice_in_roll; ++i)
        sum += rd() % die_faces + 1;

    return sum;
}
Value find_highest_frequency(const Frequencies &frequencies)
{
    Frequency it = std::max_element(
        frequencies.begin(), frequencies.end(),
        [](const std::pair<uint32_t, uint32_t> &p1, const std::pair<uint32_t, uint32_t> &p2) {
            return p1.second < p2.second;
        });

    return it != frequencies.end() ? it->first : 0;
}
} // namespace

Value get_most_frequent_dice_roll(const uint32_t dice_in_roll, const uint32_t die_faces,
                                  const uint32_t sample_size)
{
    Frequencies frequencies;

    for (uint32_t i = 0; i < sample_size; ++i)
        ++frequencies[roll_dice(dice_in_roll, die_faces)];

    return find_highest_frequency(frequencies);
}
