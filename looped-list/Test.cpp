/*      Results table
    1	2	3	4	5	6	7	8	9	10
1	1	1	1	1	1	1	1	1	1	1
2	2	1	2	1	2	1	2	1	2	1
3	3	3	2	2	1	1	3	3	2	2
4	4	1	1	2	2	3	2	3	3	4
5	5	3	4	1	2	4	4	1	2	4
6	6	5	1	5	1	4	5	3	5	2
7	7	7	4	2	6	3	5	4	7	5
8	8	1	7	6	3	1	4	4	8	7
9	9	3	1	1	8	7	2	3	8	8
10	10	5	4	5	3	3	9	1	7	8
*/
#include "List.h"
#include <gtest/gtest.h>

struct TestClass : public testing::Test
{
    const size_t n = 10;
    List* l = generate_list(n);
};


TEST_F(TestClass, generation) 
{
    List* tmp = l;
    
    for (size_t i = 1; i <= n; ++i) {
        EXPECT_EQ(i, tmp->element);
        tmp = tmp->p_next;
    }
    EXPECT_EQ(l->element, tmp->element);
}

TEST_F(TestClass, get_position1) 
{
    EXPECT_EQ(10, get_survivor(l, 1));
}

TEST_F(TestClass, get_position2) 
{
    EXPECT_EQ(5, get_survivor(l, 2));
}

TEST_F(TestClass, get_position3) 
{
    EXPECT_EQ(4, get_survivor(l, 3));
}

TEST_F(TestClass, get_position4) 
{
    EXPECT_EQ(5, get_survivor(l, 4));
}

TEST_F(TestClass, get_position5) 
{
    EXPECT_EQ(3, get_survivor(l, 5));
}

TEST_F(TestClass, get_position6) 
{
    EXPECT_EQ(3, get_survivor(l, 6));
}

TEST_F(TestClass, get_position7) 
{
    EXPECT_EQ(9, get_survivor(l, 7));
}

TEST_F(TestClass, get_position8) 
{
    EXPECT_EQ(1, get_survivor(l, 8));
}

TEST_F(TestClass, get_position9) 
{
    EXPECT_EQ(7, get_survivor(l, 9));
}

TEST_F(TestClass, get_position10) 
{
    EXPECT_EQ(8, get_survivor(l, 10));
}

TEST(List, empty_list) 
{
    List* l = nullptr;
    EXPECT_EQ(0, get_survivor(l, 5));
}