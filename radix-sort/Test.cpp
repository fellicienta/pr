#include "radix.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <random>

void generate_numbers(std::vector<ItemType> &v, const uint32_t amount, const ItemType min_value,
                      const ItemType max_value)
{
    std::random_device rd;
    std::mt19937 g(rd());

    for (uint16_t i = 0; i < amount; ++i)
        v.push_back(min_value + rd() % max_value);
}

TEST(RadixSort, manual_input)
{
    std::vector<ItemType> v = {845676, 1288, 12679, 0, 2568, 45, 7155595, 3436, 49};
    std::vector<ItemType> v2(v);

    std::sort(v2.begin(), v2.end());
    radix_sort(v);

    ASSERT_THAT(v, testing::ElementsAreArray(v2));
}

TEST(RadixSort, generated_input)
{
    std::vector<ItemType> v;
    generate_numbers(v, 1000, 50, 50000);
    std::vector<ItemType> v2(v);

    std::sort(v2.begin(), v2.end());
    radix_sort(v);

    ASSERT_THAT(v, testing::ElementsAreArray(v2));
}
