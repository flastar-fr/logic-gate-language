#pragma once

#include <vector>

#include "NodeType.hpp"

struct Node {
    Node() = default;
    explicit Node(const size_t index, const NodeType node_type) : index(index), node_type(node_type) {}

    size_t index = 0;
    std::vector<Node> neighbors;
    std::vector<Node> predecessors;
    NodeType node_type = NodeType::UNDEFINED;
    bool state = false;
};
