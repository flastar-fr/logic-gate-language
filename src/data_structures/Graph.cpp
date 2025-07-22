#include "Graph.hpp"

#include <iostream>

Graph::Graph(const int size) {
    nodes.reserve(size);
}

void Graph::add_edge(const Node& from, Node& to) {
    if (nodes.size() <= from.index) {
        nodes.resize(from.index + 1);
        nodes[from.index] = from;
    }
    nodes[from.index].neighbors.emplace_back(to);
}

void Graph::print_graph() const {
    for (size_t i = 0; i < nodes.size(); ++i) {
        std::cout << "Node " << i << ": ";
        for (const auto& neighbor : nodes[i].neighbors) {
            std::cout << neighbor.index << " ";
        }
        std::cout << std::endl;
    }
}
