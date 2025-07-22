#include "Graph.hpp"

#include <iostream>

Graph::Graph(const int size) {
    nodes.reserve(size);
}

void Graph::add_node(const Node& node) {
    nodes.emplace_back(node);
}

void Graph::add_edge(const size_t from, Node& to) {
    nodes[from].adjacents.emplace_back(to);
}

void Graph::print_graph() const {
    for (size_t i = 0; i < nodes.size(); ++i) {
        std::cout << "Node " << i << ": ";
        for (const auto& neighbor : nodes[i].adjacents) {
            std::cout << neighbor.index << " ";
        }
        std::cout << std::endl;
    }
}
