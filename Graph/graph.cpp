#include "graph.h"

#include <iterator>
#include <queue>
#include <stack>

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
    Vertex v; // Current Vertex
    used[start] = true;
    queue.push(start);

    while (!queue.empty())
    {
        v = queue.front();
        queue.pop();
        result.push_back(v);

        for (auto it : m_adjacency_list[v])
        {
            if (!used[it])
            {
                queue.push(it);
                used[it] = true;
            }
        }
    }
    return result;
}

void Graph::dfs_u(const Vertex start)
{
    std::stack<Vertex> st;
    Vertex v; // Current Vertex

    st.push(start);
    used[start] = true;

    while (!st.empty())
    {
        v = st.top();
        st.pop();
    }
    for (auto it : m_adjacency_list[v])
    {
        if (!used[it])
            dfs(it);
    }
}

std::vector<Vertex> Graph::dfs(const Vertex start)
{
    std::vector<Vertex> result;
    if (m_adjacency_list.empty())
        return result;

    std::stack<Vertex> st;
    Vertex v; // Current Vertex

    st.push(start);
    //  used[start] = true;

    while (!st.empty())
    {
        v = st.top();
        st.pop();

        if (!used[v])
        {
            result.push_back(v);
            used[v] = true;
        }

        for (auto it : m_adjacency_list[v])
        {
            if (!used[it])
            {
                st.push(it);
            }
        }
    }

    return result;
}
