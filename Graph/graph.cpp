#include "graph.h"

#include <iostream>
#include <queue>

Graph::Graph(const bool directed)
    : m_nvertices(0)
    , m_nedges(0)
    , m_directed(directed)
{
    for (int32_t i = 0; i <= MAX; ++i)
    {
        m_degree[i] = 0;
        m_edges[i] = NULL;
    }
}

void Graph::input_graph(const uint32_t n_vertices, std::multimap<Vertex, Vertex> edges)
{
    m_nvertices = n_vertices;

    for (auto x : edges)
        insert_edge(x.first, x.second, m_directed);
}

void Graph::read_graph()
{
    // int32_t m; // Number of vertices
    // int32_t x;
    // int32_t y;

    // std::cin >> m_nvertices >> m;

    // for (uint32_t i = 0; i < m; ++i)
    // {
    //     std::cin >> x >> y;
    //     insert_edge(x, y, m_directed);
    // }
}

void Graph::insert_edge(const Vertex x, const Vertex y, const bool directed)
{
    EdgeNode *tmp = new EdgeNode(y, 0);
    tmp->e_next = m_edges[x];
    m_edges[x] = tmp; // Insert at the beginning of the list
    ++m_degree[x];

    if (!directed)
        insert_edge(y, x, true);
    else
        ++m_nedges;
}

void Graph::print_graph()
{
    EdgeNode *tmp;

    for (uint32_t i = 1; i <= m_nvertices; ++i)
    {
        std::cout << i << ": ";
        tmp = m_edges[i];

        while (tmp != NULL)
        {
            std::cout << " " << tmp->e_y;
            tmp = tmp->e_next;
        }
        std::cout << std::endl;
    }
}

void Graph::initialize_search()
{
    for (uint32_t i = 1; i <= m_nvertices; ++i)
    {
        m_state[i] = UNDISCOVERED;
        // m_processed[i] = m_discovered[i] = false;
        m_parent[i] = -1;
    }
}

void Graph::bfs(const Vertex start)
{
    std::queue<int32_t> q; // The queue of vertices for processing
    int32_t v;             // Current Vertex
    int32_t y;             // Next Vertex
    EdgeNode *tmp;
    q.push(start);
    // m_discovered[start] = true;
    m_state[start] = DISCOVERED;

    while (!q.empty())
    {
        v = q.front();
        q.pop();
        process_vertex_early(v);
        //    m_processed[v] = true;
        m_state[v] = PROCESSED;
        tmp = m_edges[v];

        while (tmp != NULL)
        {
            y = tmp->e_y;
            // if (!m_processed[y] || m_directed)
            if (m_state[y] != PROCESSED || m_directed)
                process_edge(v, y);
            // if (!m_discovered[y])
            if (m_state[y] == UNDISCOVERED)
            {
                q.push(y);
                // m_discovered[y] = true;
                m_state[y] = DISCOVERED;
                m_parent[y] = v;
            }
            tmp = tmp->e_next;
        }
        process_vertex_late(v);
    }
}

void Graph::find_path(const Vertex start, const Vertex end)
{
    if (start == end || end == -1)
        std::cout << std::endl << start;
    else
    {
        find_path(start, m_parent[end]);
        std::cout << " " << end << std::endl;
    }
}

void Graph::connected_componets()
{
    uint32_t c = 0; // Number of component

    initialize_search();

    for (uint32_t i = 1; i <= m_nvertices; ++i)
    {
        if (m_state[i] == UNDISCOVERED)
        {
            ++c;
            std::cout << "Component " << i << ": ";
            bfs(i);
            std::cout << std::endl;
        }
    }
}

void Graph::dfs(const Vertex v)
{
    initialize_search();
    bool finished = false;
    EdgeNode *tmp;
    int32_t y; // Next Vertex
    if (finished)
        return;
    m_state[v] = DISCOVERED;

    process_vertex_early(v);
    tmp = m_edges[v];

    while (tmp != NULL)
    {
        y = tmp->e_y;
        if (m_state[y] == UNDISCOVERED)
        {
            m_parent[y] = v;
            process_edge(v, y);
            dfs(y);
        }
        else if (m_state[y] != PROCESSED || m_directed)
            process_edge(v, y);

        if (finished)
            return;
        tmp = tmp->e_next;
    }
    process_vertex_late(v);
    m_state[v] = PROCESSED;
}

void Graph::process_vertex_early(Vertex v)
{
    std::cout << "Processed vertex " << v << std::endl;
}

void Graph::process_edge(Vertex x, Vertex y)
{
    std::cout << "Processed edge (" << x << "," << y << ")" << std::endl;
}

void Graph::process_vertex_late(Vertex v)
{
}