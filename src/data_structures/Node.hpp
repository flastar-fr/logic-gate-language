#pragma once

#include <vector>
#include <iostream>

#include "GateData.hpp"
#include "NodeType.hpp"

struct Node {
    Node() = default;
    explicit Node(const size_t index, const NodeType node_type) : index(index), node_type(node_type) {}

    explicit Node(const size_t index, const NodeType node_type, const GateData gate_data) : index(index),
        node_type(node_type), gate_data(gate_data) {}

    size_t index = 0;
    std::vector<size_t> neighbors;
    std::vector<size_t> predecessors;
    NodeType node_type = NodeType::UNDEFINED;
    bool state = false;
    GateData gate_data{};
};

inline void add_neighbor(size_t neighbor_to_add, Node& node) {
    size_t i = 0;
    while (i < node.neighbors.size()) {
        if (node.neighbors[i] == neighbor_to_add) return;
        ++i;
    }
    node.neighbors.emplace_back(neighbor_to_add);
}

inline void add_predecessor(size_t predecessor_to_add, Node& node) {
    size_t i = 0;
    while (i < node.predecessors.size()) {
        if (node.predecessors[i] == predecessor_to_add) return;
        ++i;
    }
    node.predecessors.emplace_back(predecessor_to_add);
}

inline std::ostream& operator<<(std::ostream& lhs, const Node& rhs) {
    lhs << "Node " << rhs.index << ": ";
    lhs << "Neighbors: { ";
    for (const auto& neighbor : rhs.neighbors) {
        lhs << neighbor << " ";
    }
    lhs << "} Predecessors: { ";
    for (const auto& predecessor : rhs.predecessors) {
        lhs << predecessor << " ";
    }
    lhs << "} Type: " << rhs.node_type;
    return lhs;
}
