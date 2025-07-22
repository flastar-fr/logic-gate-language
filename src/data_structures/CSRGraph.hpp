#pragma once
#include <vector>

#include "Graph.hpp"

class CSRGraph {
public:
    explicit CSRGraph(Graph graph);

    void print_graph() const noexcept;
    [[nodiscard]] std::vector<Node>& get_edges() noexcept { return edges; }
    [[nodiscard]] std::vector<size_t>& get_offsets() noexcept { return offsets; }

private:
    std::vector<Node> edges;
    std::vector<size_t> offsets;
};
