#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <stdexcept>
#include <algorithm>
#include "graph.h"

Graph::Graph(int num_nodes)
{
    // Initialize the number of nodes used
    nodes.resize(num_nodes);
    for (int i = 0; i < num_nodes; i++)
    {
        nodes[i].id = i;
    }
}

void Graph::add_edge(int a, int b)
{
    // Prevent duplicates and self loops
    if (a == b || has_edge(a, b))
    {
        return;
    }
    nodes[a].neighbors.emplace(b);
    nodes[b].neighbors.emplace(a);
}

void Graph::remove_edge(int a, int b)
{
    auto found_a = std::find(nodes[a].neighbors.begin(), nodes[a].neighbors.end(), b);
    if (found_a != nodes[a].neighbors.end())
    {
        nodes[a].neighbors.erase(found_a);
    }

    auto found_b = std::find(nodes[b].neighbors.begin(), nodes[b].neighbors.end(), a);
    if (found_b != nodes[b].neighbors.end())
    {
        nodes[b].neighbors.erase(found_b);
    }
}

bool Graph::has_edge(int a, int b) const
{
    // Only need to search through one nodes neighbors since they are linked
    return std::find(nodes[a].neighbors.begin(), nodes[a].neighbors.end(), b) != nodes[a].neighbors.end();
}

void Graph::generate(int degree, double probability, int seed)
{
    const int num_nodes = static_cast<int>(nodes.size());

    // Validate arguments
    if (degree % 2 != 0 || degree >= num_nodes)
    {
        throw std::invalid_argument("Number of neighbors must be an even integer less than number of nodes");
    }

    std::vector<std::pair<int, int>> initial_edges;

    // Create initial ring lattice connecting each node to its nearest neighbors (num_neighbors/2 on each side)
    for (int i = 0; i < num_nodes; i++)
    {
        for (int j = 1; j <= degree / 2; j++)
        {
            int neighbor = (i + j) % num_nodes;
            add_edge(i, neighbor);
        }
    }

    // Rewire edges with probability
    std::mt19937 rand_gen(seed);
    std::uniform_real_distribution<> probability_distrobution(0.0, 1.0);
    std::uniform_int_distribution<> node_distrobution(0, num_nodes - 1);

    for (int i = 0; i < num_nodes; ++i)
    {
        // Only iterate through rightward connections to avoid checking the same edge twice
        for (int j = 1; j <= degree / 2; ++j)
        {
            if (probability_distrobution(rand_gen) < probability)
            {
                int old_neighbor = (i + j) % num_nodes;

                // Find a valid new neighbor (not self, not the old neighbor, not already connected)
                int new_neighbor = node_distrobution(rand_gen);
                int attempts = 0;

                while ((new_neighbor == i || new_neighbor == old_neighbor || has_edge(i, new_neighbor)) && attempts < num_nodes)
                {
                    new_neighbor = node_distrobution(rand_gen);
                    attempts++;
                }

                // Perform the rewire if a valid replacement node was found
                if (attempts < num_nodes)
                {
                    remove_edge(i, old_neighbor);
                    add_edge(i, new_neighbor);
                }
            }
        }
    }
}

void Graph::printGraph() const
{
    for (const auto &node : nodes)
    {
        std::cout << "Node " << node.id << " neighbors: ";
        for (int neighbor : node.neighbors)
        {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
    }
}
