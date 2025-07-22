#pragma once

#include "Node.hpp"
#include "NodeType.hpp"

struct CSRNode {
    explicit CSRNode(const Node& node) : id(node.index), node_type(node.node_type), state(node.state) {}

    size_t id = 0;
    NodeType node_type = NodeType::UNDEFINED;
    bool state = false;
};
