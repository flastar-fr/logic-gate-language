#pragma once

#include <vector>

#include "Node.hpp"

class Graph {
public:
    explicit Graph(int size);

    void add_node(const Node& node);
    void add_edge(size_t from, Node& to);
    void print_graph() const;
    [[nodiscard]] std::vector<Node>& get_nodes() noexcept { return nodes; }

private:
    std::vector<Node> nodes;
};
