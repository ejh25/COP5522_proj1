#include <iostream>
#include "graph.h"

int main()
{
    int total_nodes = 20;     // Total number of nodes in the graph
    int degree = 4;           // Mean degree (must be an even integer)
    double probability = 0.2; // Rewiring probability (0 = ring lattice, 1 = random graph)

    Graph graph = Graph(total_nodes);
    graph.generate(degree, probability);
    graph.printGraph();

    return 0;
}
