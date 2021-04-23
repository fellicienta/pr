#include "FileStringList.h"
#include <gtest/gtest.h>

TEST(FileTest, insert_new_pos)
{
    FileStringList f("noexist");
    f.insert("Mark Johnson", 1);
    f.insert("Sam Williams", 2);
    f.insert("Linda Anderson", 3);
    std::string s("Albert Reitschmidt");
    uint32_t id = 5;

    EXPECT_TRUE(f.insert(s, id));
    EXPECT_EQ(s, f.string(id));
}

TEST(FileTest, insert_existing_pos)
{
    FileStringList f("noexist");

    EXPECT_FALSE(f.insert("Linda Anderson", 3));
}

TEST(FileTest, remove_existing_string)
{
    FileStringList f("noexist");
    f.insert("Linda Anderson", 3);
    std::string s("Elina Bekenova");
    uint32_t id = 7;
    f.insert(s, id);
    EXPECT_TRUE(f.remove(id));
    EXPECT_EQ("", f.string(id));
}

TEST(FileTest, remove_nonexisting_string)
{
    FileStringList f("noexist");
    f.insert("Linda Anderson", 3);
    EXPECT_FALSE(f.remove(20));
}