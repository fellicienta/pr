#include "lib.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(HanoiTowers, even_number_of_disks)
{
    uint32_t from = 0;
    uint32_t to = 2;
    uint32_t n = 6;
    Tower t[g_size];
    make_tower(t[from], n);
    Tower expected;
    make_tower(expected, n);
    hanoi(t, from, to);

    for (int i = 0; i < n; ++i)
    {
        ASSERT_EQ(t[to].top(), expected.top());
        t[to].pop();
        expected.pop();
    }
}

TEST(HanoiTowers, odd_number_of_disks)
{
    uint32_t from = 1;
    uint32_t to = 0;
    uint32_t n = 11;
    Tower t[g_size];
    make_tower(t[from], n);
    Tower expected;
    make_tower(expected, n);
    hanoi(t, from, to);

    for (int i = 0; i < n; ++i)
    {
        ASSERT_EQ(t[to].top(), expected.top());
        t[to].pop();
        expected.pop();
    }
}

TEST(HanoiTowers, segfault)
{
    uint32_t from = 0;
    uint32_t to = 4;
    uint32_t n = 6;
    Tower t[g_size];
    make_tower(t[from], n);

    ASSERT_EXIT((hanoi(t, from, to), exit(0)), ::testing::KilledBySignal(SIGSEGV), ".*");
}

TEST(HanoiTowers, empty_towers)
{
    uint32_t from = 0;
    uint32_t to = 2;
    Tower t[g_size];
    Tower expected;
    hanoi(t, from, to);

    ASSERT_EQ(t[to].empty(), expected.empty());
}
