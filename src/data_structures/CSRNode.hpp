#pragma once

#include "Node.hpp"
#include "NodeType.hpp"

struct CSRNode {
    explicit CSRNode(const Node& node) : id(node.index), node_type(node.node_type), state(node.state), gate_data(node.gate_data) {}

    size_t id = 0;
    NodeType node_type = NodeType::UNDEFINED;
    bool state = false;
    GateData gate_data;
};
