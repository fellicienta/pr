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

TEST(main, case_4)
{
    LineSegmentSet set = {{1, 4}, {5, 7}, {2, 3}, {-1, 0}};
    OverlapPointSet result = {2, 3};
    EXPECT_EQ(result, find_max_overlap_point(set));
}

TEST(main, case_5)
{
    LineSegmentSet set = {{1, 9}, {6, 14}, {3, 9}, {5, 13}, {2, 7}};
    OverlapPointSet result = {6, 7};
    EXPECT_EQ(result, find_max_overlap_point(set));
}

TEST(main, case_6)
{
    LineSegmentSet set = {{0, 3}, {2, 6}, {5, 7}};
    OverlapPointSet result = {2, 3, 5, 6};
    EXPECT_EQ(result, find_max_overlap_point(set));
}

TEST(main, no_overlap)
{
    LineSegmentSet set = {{0, 3}, {5, 7}};
    OverlapPointSet result = {};
    EXPECT_EQ(result, find_max_overlap_point(set));
}

TEST(main, single_segment)
{
    LineSegmentSet set = {{0, 3}};
    OverlapPointSet result = {};
    EXPECT_EQ(result, find_max_overlap_point(set));
}

TEST(main, empty_set)
{
    LineSegmentSet set;
    OverlapPointSet result = {};
    EXPECT_EQ(result, find_max_overlap_point(set));
}
