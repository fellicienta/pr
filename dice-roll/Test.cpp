#include "lib.h"

#include <gtest/gtest.h>

TEST(RollDice, main)
{
    EXPECT_EQ(computation(), experiment(1000000));
}
