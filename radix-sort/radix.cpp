#include "radix.h"

#include <algorithm>
#include <map>

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
