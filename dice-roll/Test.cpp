#include "lib.h"

#include <gtest/gtest.h>

TEST(RollDice, main)
{
    EXPECT_EQ(7, roll_sample(2, 6, 100000));
}
