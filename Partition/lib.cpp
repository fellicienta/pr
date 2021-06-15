#include "lib.h"

#include <limits>

uint32_t g_max = std::numeric_limits<ItemType>::max();

namespace
{
std::vector<ItemType> get_subset(const Set &set, const uint32_t start, const uint32_t end)
{
    return std::vector<ItemType>(&set[start], &set[end]);
}

void reconstruct_partition(std::vector<Set> &result, const Set &set, const std::vector<Set> &d,
                           const uint32_t n, const uint32_t k)
{
    if (k == 1)
        result.push_back(get_subset(set, 0, n));
    else
    {
        reconstruct_partition(result, set, d, d[n - 1][k - 1], k - 1);
        result.push_back(get_subset(set, d[n - 1][k - 1], n));
    }
}

} // namespace

std::vector<Set> linear_partition(const Set &set, const uint32_t k)
{
    std::vector<Set> result;
    const uint32_t n = set.size();

    if (set.empty() || n < k)
        return result;

    std::vector<Set> table(n, std::vector<ItemType>(k));
    std::vector<Set> delimiter(n, std::vector<ItemType>(k));
    std::vector<ItemType> subset_sum(n);

    subset_sum[0] = set[0];

    for (uint32_t i = 1; i < n; ++i)
        subset_sum[i] = subset_sum[i - 1] + set[i];
    for (uint32_t i = 0; i < n; ++i)
        table[i][0] = subset_sum[i];
    for (uint32_t j = 0; j < k; ++j)
        table[0][j] = set[0];

    for (uint32_t i = 1; i < n; ++i)
    {
        for (uint32_t j = 1; j < k; ++j)
        {
            table[i][j] = g_max;
            for (uint32_t d = 0; d < i; ++d)
            {
                uint32_t cost = std::max(table[d][j - 1], subset_sum[i] - subset_sum[d]);
                if (table[i][j] > cost)
                {
                    table[i][j] = cost;
                    delimiter[i][j] = d + 1;
                }
            }
        }
    }
    reconstruct_partition(result, set, delimiter, n, k);
    return result;
}
