#include "lib.h"

#include <gtest/gtest.h>

TEST(main, case_1)
{
    LineSegmentSet set = {{0, 4}, {3, 10}, {5, 7}, {1, 4}};
    OverlapPointSet result = {3, 4};
    EXPECT_EQ(result, find_max_overlap_point(set));
}

TEST(main, case_2)
{
    LineSegmentSet set = {{0, 4}, {1, 5}, {1, 7}, {1, 4}};
    OverlapPointSet result = {1, 2, 3, 4};
    EXPECT_EQ(result, find_max_overlap_point(set));
}

TEST(main, case_3)
{
    LineSegmentSet set = {{0, 4}, {4, 5}, {3, 4}};
    OverlapPointSet result = {4};
    EXPECT_EQ(result, find_max_overlap_point(set));
}

TEST(main, empty_set)
{
    LineSegmentSet set;
    OverlapPointSet result = {};
    EXPECT_EQ(result, find_max_overlap_point(set));
}
