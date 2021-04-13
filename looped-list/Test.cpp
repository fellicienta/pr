#include "List.h"
#include <gtest/gtest.h>

class TestClass : public ::testing::Test
{
protected:
    void SetUp() override
    {
        l = generate_list(n);
    }
    void TearDown() override
    {
        //       delete l;
    }
    List *l;
    const size_t n = 10;
};

TEST_F(TestClass, generation)
{
    List *tmp = l;

    for (size_t i = 1; i <= n; ++i)
    {
        EXPECT_EQ(i, tmp->element);
        tmp = tmp->p_next;
    }
    EXPECT_EQ(l->element, tmp->element);
}

TEST_F(TestClass, get_position1)
{
    EXPECT_EQ(formula(n, 1), get_survivor(l, 1));
}

TEST_F(TestClass, get_position2)
{
    EXPECT_EQ(formula(n, 2), get_survivor(l, 2));
}

TEST_F(TestClass, get_position3)
{
    EXPECT_EQ(formula(n, 3), get_survivor(l, 3));
}

TEST_F(TestClass, get_position10)
{
    EXPECT_EQ(formula(n, 10), get_survivor(l, 10));
}

TEST(List, get_position_41)
{
    const size_t n = 41;
    List *l = generate_list(n);

    EXPECT_EQ(formula(n, 2), get_survivor(l, 2));
}

TEST(List, empty_list)
{
    List *l = nullptr;
    EXPECT_EQ(0, get_survivor(l, 5));
}