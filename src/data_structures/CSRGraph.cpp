#include "CSRGraph.hpp"

#include <iostream>

CSRGraph::CSRGraph(Graph graph) {
    const auto& nodes = graph.get_nodes();

    offsets.emplace_back(0);
    for (const auto& node : nodes) {
        const auto& adjacents = node.adjacents;
        for (const auto& adjacent : adjacents) {
            edges.emplace_back(adjacent);
        }

        const size_t offset = offsets[offsets.size() - 1] + adjacents.size();
        offsets.emplace_back(offset);
    }
}

void CSRGraph::print_graph() const noexcept {
    for (size_t i = 0; i < offsets.size() - 1; ++i) {
        std::cout << "Node " << i << ": ";
        const auto offset = offsets[i];
        const auto offset_sup = offsets[i + 1];
        for (size_t j = offset; j < offset_sup; ++j) {
            std::cout << edges[j].index << " ";
        }
        std::cout << std::endl;
    }
}
