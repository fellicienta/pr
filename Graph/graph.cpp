#include "graph.h"

#include <iterator>
#include <queue>

Graph::Graph(const uint32_t n_vertices)
    : m_nvertices(n_vertices)
{
    m_adjacency_list.resize(n_vertices + 1);
}

void Graph::input_graph(const std::vector<std::pair<Vertex, Vertex>> &edges)
{
    for (auto &x : edges)
        insert_edge(x.first, x.second);
}

void Graph::insert_edge(const Vertex x, const Vertex y)
{
    m_adjacency_list[x].push_back(y);
    m_adjacency_list[y].push_back(x);
}

std::vector<Vertex> Graph::bfs(const Vertex start)
{
    std::vector<Vertex> result;
    std::queue<Vertex> queue;
    int32_t v; // Current Vertex
    m_state[start] = DISCOVERED;
    queue.push(start);

    while (!queue.empty())
    {
        v = queue.front();
        result.push_back(v);
        result.back();

        for (auto it = m_adjacency_list[v].cbegin(); it != m_adjacency_list[v].cend(); ++it)
        {
            if (m_state[*it] == UNDISCOVERED)
            {
                queue.push(*it);
                m_state[*it] = DISCOVERED;
            }
        }
    }
    return result;
}

void Graph::dfs(const Vertex v)
{
    m_dfs_result.push_back(v);
    m_state[v] = DISCOVERED;

    for (auto it = m_adjacency_list[v].cbegin(); it != m_adjacency_list[v].cend(); ++it)
    {
        if (m_state[*it] == UNDISCOVERED)
            dfs(*it);
    }
}
