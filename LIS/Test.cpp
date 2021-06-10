#include "lis.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

bool is_equal(std::vector<ItemType> v, std::vector<std::vector<ItemType>> a)
{
    for (auto i : a)
    {
        if (std::equal(v.begin(), v.end(), i.begin()))
            return true;
    }
    return false;
}

TEST(LIS, case_1)
{
    std::vector<ItemType> v = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    std::vector<ItemType> result = {0, 4, 6, 9, 13, 15};

    ASSERT_THAT(lis(v), testing::ElementsAreArray(result));
}

TEST(LIS, case_2)
{
    std::vector<ItemType> v = {50, 3, 10, 7, 40, 80};
    std::vector<std::vector<ItemType>> result = {{3, 7, 40, 80}, {3, 10, 40, 80}};

    ASSERT_PRED2(is_equal, lis(v), result);
}

TEST(LIS, empty_sequence)
{
    std::vector<ItemType> v = {};
    std::vector<ItemType> result = {};

    ASSERT_THAT(lis(v), testing::ElementsAreArray(result));
}

TEST(LIS, 1_element)
{
    std::vector<ItemType> v = {3};
    std::vector<ItemType> result = {3};

    ASSERT_THAT(lis(v), testing::ElementsAreArray(result));
}

TEST(LIS, 2_elements)
{
    std::vector<ItemType> v = {4, 3};
    std::vector<std::vector<ItemType>> result = {{4}, {3}};

    ASSERT_PRED2(is_equal, lis(v), result);
}

TEST(LIS, 3_elements)
{
    std::vector<ItemType> v = {1, 3, 2};
    std::vector<std::vector<ItemType>> result = {{1, 2}, {1, 3}};

    ASSERT_PRED2(is_equal, lis(v), result);
}