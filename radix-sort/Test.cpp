#include "radix.h"

#include <gtest/gtest.h>

TEST(RadixSort, manual_input)
{
    std::vector<ItemType> v = {845676, 1288, 12679, 0, 2568, 45, 7155595, 3436, 49};
    std::vector<ItemType> v2(v);

    std::sort(v2.begin(), v2.end());
    radix_sort(v);

    for (uint32_t i = 0; i < v.size(); ++i)
        ASSERT_EQ(v[i], v2[i]);
}

TEST(RadixSort, generated_input)
{
    std::vector<ItemType> v;
    generate_numbers(v, 1000, 50, 50000);
    std::vector<ItemType> v2(v);

    std::sort(v2.begin(), v2.end());
    radix_sort(v);

    for (uint32_t i = 0; i < v.size(); ++i)
        ASSERT_EQ(v[i], v2[i]);
}
