#include "dstack.hpp"

#include <gtest/gtest.h>
#include <iostream>

TEST(DoubleStack, empty_stack) {
    DoubleStack<int> ds;

    EXPECT_EQ(0, ds.size(HEAD));
    EXPECT_TRUE(ds.empty(HEAD));

    EXPECT_EQ(0, ds.size(TAIL));
    EXPECT_TRUE(ds.empty(TAIL));
}

TEST(DoubleStack, non_empty_stack) {
    DoubleStack<int> ds;

    ds.push(0, TAIL);
    ds.push(0, HEAD);  

    EXPECT_FALSE(ds.empty(HEAD));
    EXPECT_FALSE(ds.empty(TAIL));
}

TEST(DoubleStack, default_case) {
    DoubleStack<int> ds;

    EXPECT_EQ(-1, ds.size(static_cast<STACK_>(3)));
    EXPECT_EQ(-1, ds.pop(static_cast<STACK_>(3)));
}

TEST(DoubleStack, push_items) {
    DoubleStack<int> ds;
    int quantity = 300;

    for (int i = 1; i <= quantity; ++i) {
        ASSERT_TRUE(ds.push(i, HEAD));
        ASSERT_TRUE(ds.push(i, TAIL));
    }

    EXPECT_EQ(quantity, ds.size(HEAD));
    EXPECT_EQ(quantity, ds.size(TAIL));
}


TEST(DoubleStack, stack_overflow) {
    DoubleStack<int> ds;
    int middle = ds.capacity() / 2;
    int quantity = ds.capacity() / 2 + 50;

    for (int i = 1; i <= quantity; ++i) {
        if (i <= middle) {
            ASSERT_TRUE(ds.push(i, TAIL));
            ASSERT_TRUE(ds.push(i, HEAD));  
        }
        if (i > middle) {
            ASSERT_FALSE(ds.push(i, TAIL));
            ASSERT_FALSE(ds.push(i, HEAD));  
        }
    }
}

TEST(DoubleStack, pop_items) {
    DoubleStack<int> ds;
    int value = 50;

    for (int i = 1; i <= value; ++i) {
        ds.push(i, HEAD);
        ds.push(i, TAIL);
    }
    
    for (int last_pop_value = value; last_pop_value >= 1; --last_pop_value) {
        ASSERT_EQ(last_pop_value, ds.pop(HEAD));
        ASSERT_EQ(last_pop_value, ds.pop(TAIL));
    }
}


