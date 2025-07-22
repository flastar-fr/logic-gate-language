#include "CSRGraph.hpp"

#include <iostream>

CSRGraph::CSRGraph(Graph graph) {
    const auto& nodes = graph.get_nodes();
    offsets.reserve(nodes.size());
    edges.reserve(nodes.size() * 2);
    csrnodes.reserve(nodes.size());

    offsets.emplace_back(0);
    for (const auto& node : nodes) {
        csrnodes.emplace_back(node);
        const auto& neighbors = node.neighbors;
        for (const auto& neighbor : neighbors) {
            edges.emplace_back(neighbor);
        }

        const size_t offset = offsets[offsets.size() - 1] + neighbors.size();
        offsets.emplace_back(offset);
    }
}

void CSRGraph::print_graph() const noexcept {
    for (size_t i = 0; i < offsets.size() - 1; ++i) {
        std::cout << "Node " << i << ": ";
        const auto offset = offsets[i];
        const auto offset_sup = offsets[i + 1];
        for (size_t j = offset; j < offset_sup; ++j) {
            std::cout << edges[j].id << " ";
        }
        std::cout << std::endl;
    }
}

void CSRGraph::process() {
    // TODO : execute from inputs
}

void CSRGraph::print_process() const noexcept {
    // TODO : print outputs
}
