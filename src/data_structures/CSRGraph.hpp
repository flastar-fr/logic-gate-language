#pragma once
#include <vector>

#include "CSRNode.hpp"
#include "Graph.hpp"
#include "NeighborRange.hpp"

class CSRGraph {
public:
    explicit CSRGraph(Graph graph);

    void print_graph() const noexcept;
    void process();
    void print_process() const noexcept;
    [[nodiscard]] NeighborRange<size_t> get_adjacent_neighbors(const CSRNode& node) noexcept;
    [[nodiscard]] std::vector<size_t>& get_edges() noexcept { return edges; }
    [[nodiscard]] std::vector<size_t>& get_offsets() noexcept { return offsets; }

private:
    std::vector<size_t> edges;
    std::vector<size_t> offsets;
    std::vector<CSRNode> csr_nodes;
    std::vector<CSRNode*> inputs;  // TODO : store inputs as size_t to csr_nodes
    std::vector<CSRNode*> outputs;  // TODO : store outputs as size_t to csr_nodes
};
