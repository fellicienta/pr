#pragma once
#include <list>
#include <map>
#include <stdint.h>
#include <vector>

using Vertex = int32_t;
using VertexList = std::list<Vertex>;
using AdjacencyList = std::map<Vertex, VertexList>;

class Graph
{
public:
    void input_graph(const std::vector<std::pair<Vertex, Vertex>> &edges);
    void insert_edge(const Vertex x, const Vertex y);
    std::vector<Vertex> bfs(const Vertex start);
    std::vector<Vertex> dfs(const Vertex v);

private:
    AdjacencyList m_adjacency_list;
    std::map<Vertex, bool> m_used;
};
