#include "graph.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class TestClass : public testing::Test
{
protected:
    void SetUp() override
    {
        g = new Graph(n);
        g->input_graph(edges);
        g2 = new Graph(n);
        g2->input_graph(edges2);
    }
    void TearDown() override
    {
        delete g;
    }
    const std::vector<std::pair<Vertex, Vertex>> edges = {{5, 1}, {5, 2}, {5, 4}, {4, 2}, {2, 3}};
    const std::vector<std::pair<Vertex, Vertex>> edges2 = {{4, 1}, {4, 5}, {1, 2},
                                                           {2, 4}, {2, 3}, {5, 3}};
    const uint32_t n = 5;
    Graph *g;
    Graph *g2;
};

TEST_F(TestClass, bfs_5)
{
    std::vector<Vertex> result = {5, 1, 2, 4, 3};
    ASSERT_THAT(g->bfs(5), testing::ElementsAreArray(result));

    std::vector<Vertex> result2 = {5, 4,3,1,2};
    ASSERT_THAT(g2->bfs(5), testing::ElementsAreArray(result2));
}

TEST_F(TestClass, bfs_4)
{
    std::vector<Vertex> result = {4, 5, 2, 1, 3};

    ASSERT_THAT(g->bfs(4), testing::ElementsAreArray(result));
}

TEST_F(TestClass, bfs_3)
{
    std::vector<Vertex> result = {3, 2, 5, 4, 1};

    ASSERT_THAT(g->bfs(3), testing::ElementsAreArray(result));
}

TEST_F(TestClass, dfs_5)
{
    std::vector<Vertex> result = {5, 1, 2, 4, 3};
    g->dfs(5);
    ASSERT_THAT(g->m_dfs_result, testing::ElementsAreArray(result));
}

TEST_F(TestClass, dfs_4)
{
    std::vector<Vertex> result = {4, 5, 1, 2, 3};
    g->dfs(4);

    ASSERT_THAT(g->m_dfs_result, testing::ElementsAreArray(result));
}

TEST(Graph, dfs)
{
    const std::vector<std::pair<Vertex, Vertex>> edges2 = {{4, 1}, {4, 5}, {1, 2},
                                                           {2, 4}, {2, 3}, {5, 3}};
    Graph *g2 = new Graph(5);
    g2->input_graph(edges2);
    std::vector<Vertex> result2 = {2, 1, 4, 5, 3};
    g2->dfs(2);
    ASSERT_THAT(g2->m_dfs_result, testing::ElementsAreArray(result2));
}