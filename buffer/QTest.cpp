#include "lib.hpp"

#include <gtest/gtest.h>
#include <iostream>

struct TestClass : testing::Test{
    Rolling_buffer<int> rb;
    void SetUp() {
        for (size_t i = 1; i <= 12; ++i)
            rb.push(i);
    }
    void TearDown() {
    }
};

TEST_F(TestClass, default_size) {   //default size is 10
    EXPECT_EQ(10, rb.capacity());
}

TEST_F(TestClass, discard_items) {  
    std::vector<int> v = {6, 7, 8, 9, 10, 11, 12};

    for (size_t i = 0; i < rb.size(); ++i)
        ASSERT_EQ(v[i], rb[i]);
}

TEST(Rolling_buffer, set_size) {  
    Rolling_buffer<int> rb(100);

    EXPECT_EQ(100, rb.capacity());
}