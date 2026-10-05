// Eli Hagedorn
// 09/21/2026
// COP5522 Project 1
#ifndef GRAPH_H
#define GRAPH_H

#include <set>
#include <vector>

const int DEFAULT_SEED = 42;

// A node of a Wattz-Strogats graph.
// A clean place to extend node information later.
struct Node
{
    // Node ID
    int id;
    // Node neighbors
    std::set<int> neighbors;
};

// A Wattz-Strogats graph
class Graph
{
private:
    std::vector<Node> nodes;

public:
    Graph(int num_nodes);

    // Add an edge to the graph between node IDs
    void add_edge(int a, int b);

    // Remove the edge between nodes given the IDs
    void remove_edge(int a, int b);

    // Check if the graph has an edge between the two nodes
    bool has_edge(int a, int b) const;

    // Generate the graph
    void generate(int degree, double probability, int seed = DEFAULT_SEED);

    // Display the graph
    void printGraph() const;
};

#endif