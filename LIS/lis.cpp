#include "lis.h"

#include <algorithm>

const uint32_t g_invalid = std::numeric_limits<uint32_t>::max();

std::vector<ItemType> lis(const std::vector<ItemType> &v)
{
    std::vector<ItemType> result;
    if (v.empty())
        return result;

    const uint32_t size = v.size();
    std::vector<uint32_t> length(size, 1);
    std::vector<uint32_t> predecessor(size, g_invalid);

    for (uint32_t i = 1; i < size; i++)
    {
        for (uint32_t j = 0; j < i; j++)
        {
            if (v[j] < v[i] && (length[j] + 1) > length[i])
            {
                length[i] = length[j] + 1;
                predecessor[i] = j;
            }
        }
    }

    uint32_t index = std::max_element(length.cbegin(), length.cend()) - length.cbegin();

    while (index != g_invalid)
    {
        result.push_back(v[index]);
        index = predecessor[index];
    }

    std::reverse(result.begin(), result.end());
    return result;
}