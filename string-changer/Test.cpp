#include "function.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(WordPack, word)
{
    std::string w = random_word();
    auto packed = pack(w);
    auto unpacked = unpack(packed);
    EXPECT_EQ(w, unpacked);
}

TEST(WordPack, empty_string)
{
    std::string w;
    auto packed = pack(w);
    auto unpacked = unpack(packed);
    EXPECT_EQ(w, unpacked);
}

TEST(WordPack, real_string)
{
    std::string w = random_string();
    auto packed = pack(w);
    auto unpacked = unpack(packed);
    EXPECT_EQ(w, unpacked);
}