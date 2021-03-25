#include "function.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(StringChanger, word)
{
    std::string origin = random_word();
    std::string copy(origin);
    word_order_changer(origin);
    word_order_changer(origin);
    EXPECT_EQ(origin, copy);
}

TEST(StringChanger, empty_string)
{
    std::string origin;
    std::string copy(origin);
    word_order_changer(origin);
    word_order_changer(origin);
    EXPECT_EQ(origin, copy);
}

TEST(StringChanger, real_string)
{
    std::string origin = random_string();
    std::string copy(origin);
    word_order_changer(origin);
    word_order_changer(origin);
    EXPECT_EQ(origin, copy);
}