#include "lib.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(Partition, case_1)
{
    Set set = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<Set> result = {{1, 2, 3, 4, 5}, {6, 7}, {8, 9}};
    EXPECT_EQ(linear_partition(set, 3), result);
}

TEST(Partition, case_2)
{
    Set set = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<Set> result = {{1, 2, 3, 4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(linear_partition(set, 2), result);
}

TEST(Partition, case_3)
{
    Set set = {3, 1, 1, 2, 2, 1};
    std::vector<Set> result = {{3, 1, 1}, {2, 2, 1}};
    EXPECT_EQ(linear_partition(set, 2), result);
}

TEST(Partition, case_4)
{
    Set set = {3, 1, 1, 2, 2, 1};
    std::vector<Set> result = {{3, 1, 1, 2, 2, 1}};
    EXPECT_EQ(linear_partition(set, 1), result);
}

TEST(Partition, case_5)
{
    Set set = {3};
    std::vector<Set> result = {{3}};
    EXPECT_EQ(linear_partition(set, 1), result);
}

TEST(Partition, case_6)
{
    Set set = {3};
    std::vector<Set> result;
    EXPECT_EQ(linear_partition(set, 3), result);
}

TEST(Partition, empty_set)
{
    Set set;
    std::vector<Set> result;
    EXPECT_EQ(linear_partition(set, 2), result);
}