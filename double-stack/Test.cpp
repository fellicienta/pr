#include "dstack.hpp"

#include <gtest/gtest.h>
#include <iostream>

struct TestStack : ::testing::Test 
{
    DoubleStack<int> ds;
    void SetUp() {
    }
    void TearDown () {
    }
};

TEST_F(TestStack, empty_head_stack) {
    EXPECT_EQ(0, ds.hs_size());
    EXPECT_EQ(true, ds.hs_empty());
}

TEST_F(TestStack, empty_tail_stack) {
    EXPECT_EQ(0, ds.ts_size());
    EXPECT_EQ(true, ds.ts_empty());
}

TEST(DoubleStack, push_head) {
    DoubleStack<int> ds;
    int quantity = 300;

    for (int i = 1; i <= quantity; ++i) 
        ds.push(i, 'h');

    EXPECT_EQ(quantity, ds.hs_size());
}

TEST(DoubleStack, push_tail) {
    DoubleStack<int> ds;
    int quantity = 300;

    for (int i = 1; i <= quantity; ++i) 
        ds.push(i, 't');

    EXPECT_EQ(quantity, ds.ts_size());
}

TEST(DoubleStack, head_overflow) {
    DoubleStack<int> ds;
    int quantity = 600;

    //push elements to the tail-stack
    for (int i = 1; i <= quantity; ++i) 
        ds.push(i, 't');
    //try to make an overflow in the head-stack
    for (int i = 1; i <= quantity; ++i) 
        ds.push(i, 'h');

    EXPECT_EQ(ds.capacity() - quantity, ds.hs_size());
}

TEST(DoubleStack, tail_overflow) {
    DoubleStack<int> ds;
    int quantity = 600;

    //push elements to the head-stack
    for (int i = 1; i <= quantity; ++i) 
        ds.push(i, 'h');
    //try to make an overflow in the tail-stack
    for (int i = 1; i <= quantity; ++i) 
        ds.push(i, 't');

    EXPECT_EQ(ds.capacity() - quantity, ds.ts_size());
}