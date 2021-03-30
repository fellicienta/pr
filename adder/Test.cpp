#include "adder.h"

#include <gtest/gtest.h>

TEST(adder, positiv_numbers) {
    EXPECT_EQ((5 + 5), logical_add(5, 5));
}

TEST(adder, negativ_numbers) {
    EXPECT_EQ((-5 + 5), logical_add(-5, 5));
}