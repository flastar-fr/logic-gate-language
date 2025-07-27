#pragma once

#include <vector>

#include "Node.hpp"

class Graph {
public:
    Graph();
    explicit Graph(int size);

    void add_node(const Node& node);
    void add_edge(const Node& from, const Node& to);
    void print_graph() const;
    void resize(const size_t new_size) { nodes.resize(new_size, Node()); }
    [[nodiscard]] std::vector<Node>& get_nodes() noexcept { return nodes; }
    [[nodiscard]] Node& operator[](size_t index) noexcept;

private:
    std::vector<Node> nodes;
};
