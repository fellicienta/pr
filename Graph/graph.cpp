#include "graph.h"

#include <boost/range/adaptor/reversed.hpp>
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

void Graph::initialize_search()
{
    for (auto &i : m_used)
        i.second = false;
}

std::vector<Vertex> Graph::bfs(const Vertex start)
{
    std::vector<Vertex> result;
    if (m_adjacency_list.empty())
        return result;
    initialize_search();

    std::queue<Vertex> queue;
    Vertex v; // Current Vertex
    m_used[start] = true;
    queue.push(start);

    while (!queue.empty())
    {
        v = queue.front();
        queue.pop();
        result.push_back(v);

        for (auto it : m_adjacency_list[v])
        {
            if (!m_used[it])
            {
                queue.push(it);
                m_used[it] = true;
            }
        }
    }
    return result;
}

std::vector<Vertex> Graph::dfs(const Vertex start)
{
    std::vector<Vertex> result;
    if (m_adjacency_list.empty())
        return result;

    initialize_search();
    std::stack<Vertex> st;
    Vertex v; // Current Vertex
    st.push(start);

    while (!st.empty())
    {
        v = st.top();
        st.pop();

        if (m_used[v])
            continue;

        m_used[v] = true;
        result.push_back(v);

        for (auto it : boost::adaptors::reverse(m_adjacency_list[v]))
        {
            if (!m_used[it])
                st.push(it);
        }
    }
    return result;
}
