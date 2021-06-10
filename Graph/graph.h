#pragma once
#include <list>
#include <map>
#include <stdint.h>
#include <vector>

using Vertex = int32_t;
using VertexList = std::list<Vertex>;
using AdjacencyList = std::map<Vertex, VertexList>;

enum STATE_
{
    UNDISCOVERED,
    DISCOVERED
};

struct Graph
{
public:
    void input_graph(const std::vector<std::pair<Vertex, Vertex>> &edges);
    void insert_edge(const Vertex x, const Vertex y);
    std::vector<Vertex> bfs(const Vertex start);
    void dfs(const Vertex v);
    std::vector<Vertex> get_dfs_result();

private:
    AdjacencyList m_adjacency_list;
    std::map<Vertex, STATE_> m_state;
    std::vector<Vertex> m_dfs_result;
};
