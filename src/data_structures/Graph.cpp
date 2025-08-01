#include "Graph.hpp"

#include <iostream>

Graph::Graph() : Graph(1) {}

Graph::Graph(const int size) {
    resize(size);
}

void Graph::add_node(const Node& node) {
    if (node.index >= nodes.size()) {
        resize((node.index + 1) * 2);
    }

    nodes[node.index].index = node.index;
    nodes[node.index].node_type = node.node_type;
    nodes[node.index].state = node.state;
    nodes[node.index].gate_data = node.gate_data;
    nodes[node.index].neighbors = node.neighbors;
    nodes[node.index].predecessors = node.predecessors;
}

void Graph::add_edge(const Node& from, const Node& to) {
    add_node(from);
    add_node(to);

    nodes[from.index].neighbors.emplace_back(to.index);
    nodes[to.index].predecessors.emplace_back(from.index);
}

void Graph::print_graph() const {
    for (const auto& node : nodes) {
        std::cout << node << std::endl;
    }
}

[[nodiscard]] Node& Graph::operator[](const size_t index) noexcept {
    if (index > nodes.size()) resize(index * 2);
    return nodes[index];
}
