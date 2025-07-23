#pragma once
#include <vector>

#include "CSRNode.hpp"
#include "Graph.hpp"
#include "NeighborRange.hpp"

class CSRGraph {
public:
    explicit CSRGraph(Graph graph);

    void print_graph() noexcept;
    void execute_wire_propagation(CSRNode& node, NeighborRange<size_t> predecessors) const;
    void propagate();
    void print_states() const noexcept;
    void construct_routing() noexcept;
    [[nodiscard]] std::vector<size_t> bfs(size_t from);
    [[nodiscard]] NeighborRange<size_t> get_neighbors(size_t node) noexcept;
    [[nodiscard]] NeighborRange<size_t> get_predecessors(size_t node) noexcept;
    [[nodiscard]] std::vector<size_t>& get_edges() noexcept { return edges; }
    [[nodiscard]] std::vector<size_t>& get_offsets() noexcept { return offsets; }

private:
    std::vector<size_t> edges;
    std::vector<size_t> edges_predecessors;
    std::vector<size_t> offsets;
    std::vector<size_t> offsets_predecessors;
    std::vector<CSRNode> csr_nodes;
    std::vector<size_t> inputs;
    std::vector<size_t> outputs;
    std::vector<size_t> order_to_propagate;
};
