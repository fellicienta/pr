#include "lib.h"

#include <gtest/gtest.h>

TEST(RollDice, main)
{
    EXPECT_EQ(computation(6), experiment(2, 6, 1000000));
    EXPECT_EQ(computation(12), experiment(2, 12, 100000));
}
