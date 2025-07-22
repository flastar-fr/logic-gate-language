#include "Graph.hpp"

#include <iostream>

Graph::Graph(const int size) : nodes(size) {}

void Graph::add_edge(const size_t from, const size_t to) {
    nodes[from].adjacents.emplace_back(to);
}

void Graph::print_graph() const {
    for (size_t i = 0; i < nodes.size(); ++i) {
        std::cout << "Node " << i << ": ";
        for (const auto& neighbor : nodes[i].adjacents) {
            std::cout << neighbor.index << " ";
        }
        std::cout << "\n";
    }
}
