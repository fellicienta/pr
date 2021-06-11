#include "graph.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class TestClass : public testing::Test
{
public:
    static void SetUpTestCase()
    {
        g.input_graph(edges);
        g2.input_graph(edges2);
    }

protected:
    static std::vector<std::pair<Vertex, Vertex>> edges;
    static std::vector<std::pair<Vertex, Vertex>> edges2;
    static Graph g;
    static Graph g2;
};

Graph TestClass::g;
Graph TestClass::g2;
std::vector<std::pair<Vertex, Vertex>> TestClass::edges = {{5, 1}, {5, 2}, {5, 4}, {4, 2}, {2, 3}};
std::vector<std::pair<Vertex, Vertex>> TestClass::edges2 = {{4, 7}, {4, 5}, {7, 2},
                                                            {2, 4}, {2, 3}, {5, 3}};

TEST_F(TestClass, bfs_5)
{
    std::vector<Vertex> result = {5, 1, 2, 4, 3};
    ASSERT_THAT(g.bfs(5), testing::ElementsAreArray(result));

    std::vector<Vertex> result2 = {5, 4, 3, 7, 2};
    ASSERT_THAT(g2.bfs(5), testing::ElementsAreArray(result2));
}

TEST_F(TestClass, bfs_4)
{
    std::vector<Vertex> result = {4, 5, 2, 1, 3};
    ASSERT_THAT(g.bfs(4), testing::ElementsAreArray(result));

    std::vector<Vertex> result2 = {4, 7, 5, 2, 3};
    ASSERT_THAT(g2.bfs(4), testing::ElementsAreArray(result2));
}

TEST_F(TestClass, bfs_3)
{
    std::vector<Vertex> result = {3, 2, 5, 4, 1};
    ASSERT_THAT(g.bfs(3), testing::ElementsAreArray(result));

    std::vector<Vertex> result2 = {3, 2, 5, 7, 4};
    ASSERT_THAT(g2.bfs(3), testing::ElementsAreArray(result2));
}

TEST_F(TestClass, dfs_5)
{
    std::vector<Vertex> result = {5, 1, 2, 4, 3};
    ASSERT_THAT(g.dfs(5), testing::ElementsAreArray(result));

    std::vector<Vertex> result2 = {5, 4, 7, 2, 3};
    ASSERT_THAT(g2.dfs(5), testing::ElementsAreArray(result2));
    std::vector<Vertex> result3 = {5, 4, 3, 7, 2};
    ASSERT_THAT(g2.bfs(5), testing::ElementsAreArray(result3));
    ASSERT_THAT(g2.bfs(5), testing::ElementsAreArray(result3));
}

TEST_F(TestClass, dfs_4)
{
    std::vector<Vertex> result = {4, 5, 1, 2, 3};
    ASSERT_THAT(g.dfs(4), testing::ElementsAreArray(result));

    std::vector<Vertex> result2 = {4, 7, 2, 3, 5};
    ASSERT_THAT(g2.dfs(4), testing::ElementsAreArray(result2));
}

TEST_F(TestClass, dfs_2)
{
    std::vector<Vertex> result = {2, 5, 1, 4, 3};
    ASSERT_THAT(g.dfs(2), testing::ElementsAreArray(result));

    std::vector<Vertex> result2 = {2, 7, 4, 5, 3};
    ASSERT_THAT(g2.dfs(2), testing::ElementsAreArray(result2));
}

TEST(Graph, empty_graph)
{
    static Graph g;
    std::vector<Vertex> result = {};
    ASSERT_THAT(g.bfs(2), testing::ElementsAreArray(result));
    ASSERT_THAT(g.dfs(2), testing::ElementsAreArray(result));
}
