#include "Graph.hpp"

#include <iostream>

Graph::Graph(const int size) {
    nodes.resize(size, Node());
}

void Graph::add_edge(const Node& from, const Node& to) {
    nodes[from.index].index = from.index;
    nodes[from.index].node_type = from.node_type;
    nodes[from.index].state = from.state;
    nodes[to.index].index = to.index;
    nodes[to.index].node_type = to.node_type;
    nodes[to.index].state = to.state;
    nodes[from.index].neighbors.emplace_back(to.index);
    nodes[to.index].predecessors.emplace_back(from.index);
}

void Graph::print_graph() const {
    for (size_t i = 0; i < nodes.size(); ++i) {
        std::cout << "Node " << i << ": ";
        std::cout << "Neighbors: ";
        for (const auto& neighbor : nodes[i].neighbors) {
            std::cout << neighbor << " ";
        }
        std::cout << "Predecessors: ";
        for (const auto& predecessor : nodes[i].predecessors) {
            std::cout << predecessor << " ";
        }
        std::cout << std::endl;
    }
}
