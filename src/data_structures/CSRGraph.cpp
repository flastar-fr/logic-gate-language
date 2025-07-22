#include "CSRGraph.hpp"

#include <iostream>

CSRGraph::CSRGraph(Graph graph) {
    const auto& nodes = graph.get_nodes();
    offsets.reserve(nodes.size());
    edges.reserve(nodes.size() * 2);
    csr_nodes.reserve(nodes.size());

    offsets.emplace_back(0);
    for (auto& node : nodes) {
        csr_nodes.emplace_back(node);
        auto& added_node = csr_nodes.back();

        const auto& neighbors = node.neighbors;
        for (const auto& neighbor : neighbors) {
            edges.emplace_back(neighbor.index);
        }

        if (node.node_type == NodeType::INPUT) inputs.emplace_back(&added_node);
        if (node.node_type == NodeType::OUTPUT) outputs.emplace_back(&added_node);

        const size_t offset = offsets.back() + neighbors.size();
        offsets.emplace_back(offset);
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

    for (const auto input : inputs) {
        for (const auto& neighbor : get_adjacent_neighbors(*input)) {
            csr_nodes[neighbor].state = input->state;
            // TODO : implement BFS going for each inputs and switching the state correctly
        }

    }
}

void CSRGraph::print_process() const noexcept {
    for (const auto input : inputs) {
        std::cout << "Input " << input->id << ": " << input->state << std::endl;
    }
    for (const auto output : outputs) {
        std::cout << "Output " << output->id << ": " << output->state << std::endl;
    }
}

NeighborRange<size_t> CSRGraph::get_adjacent_neighbors(const CSRNode& node) noexcept {
    return NeighborRange(&edges[offsets[node.id]], &edges[offsets[node.id + 1]]);
}
