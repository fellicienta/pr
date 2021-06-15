#include "lib.h"

namespace
{
std::vector<ItemType> get_subset(const Set &set, const uint32_t start, const uint32_t end)
{
    return std::vector<ItemType>(&set[start - 1], &set[end]);
}
void reconstruct_partition(std::vector<Set> &result, const Set &set, const std::vector<Set> &d,
                           const uint32_t n, const uint32_t k)
{
    if (k == 1)
        result.push_back(get_subset(set, 1, n));
    else
    {
        reconstruct_partition(result, set, d, d[n][k], k - 1);
        result.push_back(get_subset(set, d[n][k] + 1, n));
    }
}

} // namespace

std::vector<Set> linear_partition(const Set &set, const uint32_t k)
{
    std::vector<Set> result;
    const uint32_t n = set.size();
    if (set.empty() || n < k)
        return result;

    std::vector<Set> table(n + 1, std::vector<ItemType>(k + 1));
    std::vector<Set> delimiter(n + 1, std::vector<ItemType>(k + 1));
    std::vector<ItemType> subset_sum(n + 1);
    uint32_t cost;
    subset_sum[0] = 0;

    for (uint32_t i = 0; i < n; ++i)
        subset_sum[i + 1] = subset_sum[i] + set[i];
    for (uint32_t i = 1; i <= n; ++i)
        table[i][1] = subset_sum[i];
    for (uint32_t j = 1; j <= k; ++j)
        table[1][j] = set[0];

    for (uint32_t i = 2; i <= n; ++i)
    {
        for (uint32_t j = 2; j <= k; ++j)
        {
            table[i][j] = 1000;
            for (uint32_t d = 1; d <= (i - 1); ++d)
            {
                cost = std::max(table[d][j - 1], subset_sum[i] - subset_sum[d]);
                if (table[i][j] > cost)
                {
                    table[i][j] = cost;
                    delimiter[i][j] = d;
                }
            }
        }
    }
    reconstruct_partition(result, set, delimiter, n, k);
    return result;
}
