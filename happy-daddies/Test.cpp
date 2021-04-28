#include "lib.h"

#include <gtest/gtest.h>

TEST(HappyDaddies, test)
{
    EXPECT_NEAR(1.0, get_ratio(), 1.0 / 10);
}