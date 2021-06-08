#pragma once
#include <map>
#include <stdint.h>
#include <vector>

using Vertex = int32_t;

const uint32_t MAX = 100;

enum STATE_
{
    UNDISCOVERED,
    DISCOVERED,
    PROCESSED
};

struct Graph
{
public:
    Graph(const bool directed);
    void read_graph();
    void input_graph(const uint32_t n_vertices, std::multimap<Vertex, Vertex> edges);
    void insert_edge(const Vertex x, const Vertex y, const bool directed);
    void print_graph();
    void bfs(const Vertex start);
    void find_path(const Vertex start, const Vertex end);
    void connected_componets();
    void dfs(const Vertex v);

private:
    class EdgeNode
    {
    public:
        EdgeNode(const Vertex y, const uint32_t weight)
            : e_y(y)
            , e_weight(weight)
        {
        }
        Vertex e_y;        // Adjacency info
        uint32_t e_weight; // Edge weight, if exists
        EdgeNode *e_next;  // Next edge in the list
    };
    void initialize_search();
    void process_vertex_late(const Vertex v);
    void process_vertex_early(const Vertex v);
    void process_edge(const Vertex x, const Vertex y);

    EdgeNode *m_edges[MAX + 1]; // Adjacency info
    uint32_t m_degree[MAX + 1]; // Degree of each vertice
    uint32_t m_nvertices;       // Number of vertices in the graph
    uint32_t m_nedges;          // Number of edges in the graph
    bool m_directed;            // Is graph directed ?

    std::map<Vertex, STATE_> m_state;
    // bool m_processed[MAX];
    // bool m_discovered[MAX];
    std::map<Vertex, Vertex> m_parent;
    uint32_t m_entry_time[MAX];
};
