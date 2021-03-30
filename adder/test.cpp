#include "adder.h"

#include <gtest/gtest.h>

TEST(adder, positiv_numbers) {
    EXPECT_EQ((5 + 5), logical_add(5, 5));
}
/*
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
*/