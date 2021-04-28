#include "lib.h"

#include <gtest/gtest.h>

TEST(HappyDaddies, test)
{
    double expectation = 1.0;
    double error = expectation / 10;

    EXPECT_NEAR(expectation, get_ratio1(), error);
    EXPECT_NEAR(expectation, get_ratio2(), error);
}