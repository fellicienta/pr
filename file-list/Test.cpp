#include "FileStringList.h"

#include <gtest/gtest.h>

TEST(FileTest, insert)
{
    FileStringList f("file4");
    std::string s1("First string");
    std::string s2("Second string");
    std::string s3("Third string");
    std::string s4("Fourth string");
    std::string s5("Fifth string");
    std::string s6("Sixth string");
    std::string s7("Seventh string");
    std::string s8("Eigth string");

    EXPECT_TRUE(f.insert(s1, 1));  // s1
    EXPECT_TRUE(f.insert(s2, 2));  // s1 s2
    EXPECT_TRUE(f.insert(s3, 3));  // s1 s2 s3
    EXPECT_TRUE(f.insert(s4, 4));  // s1 s2 s3 s4
    EXPECT_TRUE(f.remove(2));      // s1 s3 s4
    EXPECT_TRUE(f.insert(s5, 3));  // s1 s3 s5 s4
    EXPECT_TRUE(f.insert(s6, 10)); // s1 s3 s5 s4 s6
    EXPECT_TRUE(f.remove(1));      // s3 s5 s4 s6
    EXPECT_TRUE(f.insert(s7, 2));  // s3 s7 s5 s4 s6
    EXPECT_TRUE(f.insert(s8, 2));  // s3 s8 s7 s5 s4 s6

    EXPECT_EQ(s3, f.string(1));
    EXPECT_EQ(s8, f.string(2));
    EXPECT_EQ(s7, f.string(3));
    EXPECT_EQ(s5, f.string(4));
    EXPECT_EQ(s4, f.string(5));
    EXPECT_EQ(s6, f.string(6));
}
