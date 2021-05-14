#include "lib.h"

#include <gtest/gtest.h>

TEST(CorrectBrackets, one_couple)
{
    EXPECT_EQ("Success", check_brackets("[]"));
}

TEST(CorrectBrackets, many_couples)
{
    EXPECT_EQ("Success", check_brackets("([](){([])})"));
}

TEST(CorrectBrackets, function_call)
{
    EXPECT_EQ("Success", check_brackets("foo(bar);"));
}

TEST(IncorrectBrackets, 1_case)
{
    EXPECT_EQ("3", check_brackets("[]([]"));
}

TEST(IncorrectBrackets, 2_case)
{
    EXPECT_EQ("3", check_brackets("{[}"));
}

TEST(IncorrectBrackets, function_call)
{
    EXPECT_EQ("10", check_brackets("foo(bar[i);"));
}
