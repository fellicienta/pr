#include "function.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(StringChanger, word)
{
    std::string origin = random_word();
    auto reversed = word_order_changer(origin);
    auto get_origin = word_order_changer(reversed);
    EXPECT_EQ(origin, get_origin);
}

TEST(StringChanger, empty_string)
{
    std::string origin;
    auto reversed = word_order_changer(origin);
    auto get_origin = word_order_changer(reversed);
    EXPECT_EQ(origin, get_origin);
}

TEST(StringChanger, real_string)
{
    std::string origin = random_string();
    auto reversed = word_order_changer(origin);
    auto get_origin = word_order_changer(reversed);
    EXPECT_EQ(origin, get_origin);
}