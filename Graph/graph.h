#pragma once
#include <list>
#include <map>
#include <stdint.h>
#include <vector>

using Vertex = int32_t;
using VertexList = std::list<Vertex>;
using AdjacencyList = std::vector<VertexList>;

enum STATE_
{
    UNDISCOVERED,
    DISCOVERED
};

struct Graph
{
public:
    Graph(const uint32_t n_vertices);
    void input_graph(const std::vector<std::pair<Vertex, Vertex>> &edges);
    std::vector<Vertex> bfs(const Vertex start);
    void dfs(const Vertex v);

    std::vector<Vertex> m_dfs_result;

private:
    void insert_edge(const Vertex x, const Vertex y);

    AdjacencyList m_adjacency_list;
    uint32_t m_nvertices;
    std::map<Vertex, STATE_> m_state;
};
