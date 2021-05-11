#include "lib.h"

#include <gtest/gtest.h>

TEST(RollDice, main)
{
    EXPECT_EQ(7, get_most_frequent_dice_roll(2, 6, 100000));
}
