#pragma once

#include <vector>

#include "GateData.hpp"
#include "NodeType.hpp"

struct Node {
    Node() = default;
    explicit Node(const size_t index, const NodeType node_type) : index(index), node_type(node_type) {}
    explicit Node(const size_t index, const NodeType node_type, GateData gate_data) : index(index), node_type(node_type), gate_data(gate_data) {}

    size_t index = 0;
    std::vector<size_t> neighbors;
    std::vector<size_t> predecessors;
    NodeType node_type = NodeType::UNDEFINED;
    bool state = false;
    GateData gate_data{};
};
