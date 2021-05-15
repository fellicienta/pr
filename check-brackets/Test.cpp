#include "lib.h"

#include <gtest/gtest.h>

TEST(CorrectBrackets, one_couple)
{
    std::string s("[]");
    EXPECT_EQ("Success", check_result(check_brackets(s)));
}

TEST(CorrectBrackets, many_couples)
{
    std::string s("([](){([])})");
    EXPECT_EQ("Success", check_result(check_brackets(s)));
}

TEST(CorrectBrackets, function_call)
{
    std::string s("foo(bar);");
    EXPECT_EQ("Success", check_result(check_brackets(s)));
}

TEST(IncorrectBrackets, 1_case)
{
    std::string s("[]([]");
    EXPECT_EQ("3", check_result(check_brackets(s)));
}

TEST(IncorrectBrackets, 2_case)
{
    std::string s("{[}");
    EXPECT_EQ("3", check_result(check_brackets(s)));
}

TEST(IncorrectBrackets, function_call)
{
    std::string s("foo(bar[i);");
    EXPECT_EQ("10", check_result(check_brackets(s)));
}
