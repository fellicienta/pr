#include "adder.h"

#include <gtest/gtest.h>

TEST(adder, positiv_numbers) {
    uint32_t a = rand_number();
    uint32_t b = rand_number();
    
    EXPECT_EQ((a + b), logical_add(a, b));
}

TEST(adder, 1negativ_number) {
    uint32_t a = rand_number();
    uint32_t b = rand_number();
    
    EXPECT_EQ((-a + b), logical_add(-a, b));
}

TEST(adder, 2negativ_numbers) {
    uint32_t a = rand_number();
    uint32_t b = rand_number();
    
    EXPECT_EQ((-a + -b), logical_add(-a, -b));
}

TEST(adder, big_numbers) {
    EXPECT_EQ((999999 + 999999), logical_add(999999, 999999));
}

TEST(adder, zero) {
    EXPECT_EQ((0 + 0), logical_add(0, 0));
}