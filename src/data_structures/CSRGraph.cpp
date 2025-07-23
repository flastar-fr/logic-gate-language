#include "CSRGraph.hpp"

#include <iostream>

CSRGraph::CSRGraph(Graph graph) {
    const auto& nodes = graph.get_nodes();
    offsets.reserve(nodes.size());
    edges.reserve(nodes.size() * 2);
    csr_nodes.reserve(nodes.size());

    size_t current_node = 0;
    offsets.emplace_back(0);
    for (auto& node : nodes) {
        csr_nodes.emplace_back(node);

        const auto& neighbors = node.neighbors;
        for (const auto& neighbor : neighbors) {
            edges.emplace_back(neighbor.index);
        }

        if (node.node_type == NodeType::INPUT) inputs.emplace_back(current_node);
        if (node.node_type == NodeType::OUTPUT) outputs.emplace_back(current_node);

        const size_t offset = offsets.back() + neighbors.size();
        offsets.emplace_back(offset);

        ++current_node;
    }
}

void CSRGraph::print_graph() const noexcept {
    for (size_t i = 0; i < offsets.size() - 1; ++i) {
        std::cout << "Node " << i << ": ";
        const auto offset = offsets[i];
        const auto offset_sup = offsets[i + 1];
        for (size_t j = offset; j < offset_sup; ++j) {
            std::cout << edges[j] << " ";
        }
        std::cout << std::endl;
    }
}

void CSRGraph::process() {
    std::vector<CSRNode*> nodes_to_check;
    nodes_to_check.reserve(csr_nodes.size());

    for (const auto i_input : inputs) {
        const auto& input = csr_nodes[i_input];
        for (const auto& neighbor : get_adjacent_neighbors(input)) {
            csr_nodes[neighbor].state = input.state;
            // TODO : implement BFS going for each inputs and switching the state correctly
        }

    }
}

void CSRGraph::print_process() const noexcept {
    for (const auto i_input : inputs) {
        const auto& input = csr_nodes[i_input];
        std::cout << "Input " << input.id << ": " << input.state << std::endl;
    }
    for (const auto i_output : outputs) {
        const auto& output = csr_nodes[i_output];
        std::cout << "Output " << output.id << ": " << output.state << std::endl;
    }
}

NeighborRange<size_t> CSRGraph::get_adjacent_neighbors(const CSRNode& node) noexcept {
    return NeighborRange(&edges[offsets[node.id]], &edges[offsets[node.id + 1]]);
}
