#include "radix.h"

#include <algorithm>
#include <map>
#include <random>

void generate_numbers(std::vector<ItemType> &v, const uint32_t amount, const uint32_t a,
                      const uint32_t b)
{
    std::random_device rd;
    std::mt19937 g(rd());

    for (uint16_t i = 0; i < amount; ++i)
        v.push_back(a + rd() % b);
}

namespace
{
void counting_sort(std::vector<ItemType> &v, const uint32_t digit)
{
    std::map<uint32_t, uint32_t> count;

    for (auto i : v)
        ++count[i / digit % 10];

    for (uint32_t i = 1; i < 10; ++i)
        count[i] += count[i - 1];

    std::vector<ItemType> temp(v.size());

    for (int32_t i = v.size() - 1; i >= 0; --i)
    {
        temp[count[v[i] / digit % 10] - 1] = v[i];
        count[v[i] / digit % 10]--;
    }
    v.swap(temp);
}
} // namespace

void radix_sort(std::vector<ItemType> &v)
{
    const ItemType max = *std::max_element(v.begin(), v.end());

    for (uint32_t i = 1; max / i > 0; i *= 10)
        counting_sort(v, i);
}
