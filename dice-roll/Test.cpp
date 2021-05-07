#include "lib.h"

#include <gtest/gtest.h>

TEST(RollDice, main)
{
    EXPECT_EQ(computation(6), roll_sample(2, 6, 100000));
    EXPECT_EQ(computation(12), roll_sample(2, 12, 100000));
}
