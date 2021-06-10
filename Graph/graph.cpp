#include "graph.h"

#include <iterator>
#include <queue>

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

void Graph::bfs(const Vertex start)
{
    std::queue<Vertex> queue;
    int32_t v; // Current Vertex
    used[start] = true;
    queue.push(start);

    while (!queue.empty())
    {
        v = queue.front();
        queue.pop();
        m_bfs_result.push_back(v);

        for (auto it : m_adjacency_list[v])
        {
            if (!used[it])
            {
                queue.push(it);
                used[it] = true;
            }
        }
    }
}

void Graph::dfs(const Vertex v)
{
    m_dfs_result.push_back(v);
    used[v] = true;

    for (auto it : m_adjacency_list[v])
    {
        if (!used[it])
            dfs(it);
    }
}

std::vector<Vertex> Graph::get_bfs_result()
{
    return m_bfs_result;
}

std::vector<Vertex> Graph::get_dfs_result()
{
    return m_dfs_result;
}
