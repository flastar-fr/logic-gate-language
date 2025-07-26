#pragma once
#include <stack>
#include <unordered_set>
#include <vector>

#include "CSRNode.hpp"
#include "Graph.hpp"
#include "NeighborRange.hpp"

class CSRGraph {
public:
    explicit CSRGraph(Graph graph);

    void print_graph() noexcept;
    void execute_wire_propagation(CSRNode& node, NeighborRange<size_t> predecessors) const;
    void execute_gate_prerendered_propagation(const CSRNode& node, NeighborRange<size_t> predecessors, NeighborRange<size_t> neighbors);
    void execute_gate_propagation(const CSRNode& node, NeighborRange<size_t> predecessors, NeighborRange<size_t> neighbors);
    void propagate();
    void print_states() const noexcept;
    void visit_branch(std::unordered_set<size_t>& to_visit, std::stack<size_t>& current_branch,
                      std::vector<size_t>& topological_order);
    void construct_routing() noexcept;
    [[nodiscard]] GateData determine_graph_gate_data() noexcept;
    void set_inputs_with_value(size_t values_to_verify) noexcept;
    [[nodiscard]] NeighborRange<size_t> get_neighbors(size_t node) noexcept;
    [[nodiscard]] NeighborRange<size_t> get_predecessors(size_t node) noexcept;
    [[nodiscard]] std::vector<size_t>& get_edges() noexcept { return edges; }
    [[nodiscard]] std::vector<size_t>& get_offsets() noexcept { return offsets; }
    [[nodiscard]] std::vector<size_t>& get_inputs() noexcept { return inputs; }
    [[nodiscard]] std::vector<size_t>& get_outputs() noexcept { return outputs; }
    [[nodiscard]] std::vector<CSRNode>& get_csr_nodes() noexcept { return csr_nodes; }

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
