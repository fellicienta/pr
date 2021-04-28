#include "FileStringList.h"
#include <gtest/gtest.h>

class TestClass : public testing::Test
{
public:
    TestClass()
        : file_name("file")
        , f(file_name)
    {
    }

protected:
    void SetUp()
    {
        f.insert("First string to 1 pos", 1);
        f.insert("Second string to 2 pos", 2);
        f.insert("Third string to 1 pos", 1);
        f.insert("Fourth string to 6 pos", 6);
    }

    std::string file_name;
    FileStringList f;
};

TEST_F(TestClass, common_test)
{
    // insert
    std::string str("Adding new string");
    f.insert(str, 2);
    EXPECT_EQ(str, f.string(2));

    // remove
    str = "Remove-test";
    f.insert(str, 3);
    EXPECT_TRUE(f.remove(3));
    EXPECT_NE(str, f.string(3));

    // get a non-existent position
    EXPECT_EQ("", f.string(100));
}
