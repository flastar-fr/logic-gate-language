#include "CSRGraph.hpp"

#include <algorithm>
#include <iostream>
#include <queue>

CSRGraph::CSRGraph(Graph graph) {
    const auto& nodes = graph.get_nodes();
    offsets.reserve(nodes.size());
    edges.reserve(nodes.size() * 2);
    csr_nodes.reserve(nodes.size());

    size_t current_node = 0;
    offsets.emplace_back(0);
    offsets_predecessors.emplace_back(0);
    for (auto& node : nodes) {
        csr_nodes.emplace_back(node);

        const auto& neighbors = node.neighbors;
        edges.insert(edges.end(), neighbors.begin(), neighbors.end());

        const auto& predecessors = node.predecessors;
        edges_predecessors.insert(edges_predecessors.end(), predecessors.begin(), predecessors.end());

        if (node.node_type == NodeType::INPUT) inputs.emplace_back(current_node);
        if (node.node_type == NodeType::OUTPUT) outputs.emplace_back(current_node);

        const size_t offset = offsets.back() + neighbors.size();
        offsets.emplace_back(offset);

        const size_t offset_predecessor = offsets_predecessors.back() + predecessors.size();
        offsets_predecessors.emplace_back(offset_predecessor);

        ++current_node;
    }

    construct_routing();
}

void CSRGraph::print_graph() noexcept {
    for (size_t i = 0; i < offsets.size() - 1; ++i) {
        std::cout << "Node " << i << ": ";
        std::cout << "Neighbors: ";
        for (const auto& neighbor : get_neighbors(i)) {
            std::cout << csr_nodes[neighbor].id << " ";
        }
        std::cout << "Predecessors: ";
        for (const auto& predecessor : get_predecessors(i)) {
            std::cout << csr_nodes[predecessor].id << " ";
        }
        std::cout << std::endl;
    }
}

void CSRGraph::execute_wire_propagation(CSRNode& node, const NeighborRange<size_t> predecessors) const {
    const bool state_to_assign = std::any_of(predecessors.begin(), predecessors.end(),
                                             [this](const size_t pred) { return csr_nodes[pred].state; });

    node.state = state_to_assign;
}

void CSRGraph::execute_gate_prerendered_propagation(CSRNode& node, const NeighborRange<size_t> predecessors) const {
    size_t truth_table_index = 0;
    for (const auto predecessor : predecessors) {
        truth_table_index <<= 1;
        if (csr_nodes[predecessor].state) {
            truth_table_index |= 1;
        }
    }

    node.state = node.gate_data.truth_table >> truth_table_index & 1;
}

void CSRGraph::execute_gate_propagation(CSRNode& node, const NeighborRange<size_t> predecessors) const {
    switch (node.gate_data.render_type) {
        case GateRenderType::PRERENDERED: {
            execute_gate_prerendered_propagation(node, predecessors);
            break;
        }
        default: {
            std::cerr << "Uknown render type" << std::endl;
            throw std::invalid_argument("Unknown render type");
        }
    }
}

void CSRGraph::propagate() {
    for (const auto i_node : order_to_propagate) {
        auto& node = csr_nodes[i_node];
        const auto predecessors = get_predecessors(i_node);
        switch (node.node_type) {
            case NodeType::INPUT:
            case NodeType::OUTPUT:
            case NodeType::WIRE: {
                execute_wire_propagation(node, predecessors);
                break;
            }
            case NodeType::GATE: {
                execute_gate_propagation(node, predecessors);
                break;
            }
            default: {
                std::cerr << "Uknown node type" << std::endl;
                throw std::invalid_argument("Unknown node type");
            }
        }
    }
}

void CSRGraph::print_states() const noexcept {
    for (const auto i_input : inputs) {
        const auto& input = csr_nodes[i_input];
        std::cout << "Input " << input.id << ": " << input.state << std::endl;
    }
    for (const auto i_output : outputs) {
        const auto& output = csr_nodes[i_output];
        std::cout << "Output " << output.id << ": " << output.state << std::endl;
    }
}

void CSRGraph::construct_routing() noexcept {
    order_to_propagate.reserve(csr_nodes.size() / 2 * inputs.size());
    for (const auto i_input : inputs) {
        for (auto node : bfs(i_input)) {
            order_to_propagate.push_back(node);
        }
    }
}

std::vector<size_t> CSRGraph::bfs(const size_t from) {
    std::vector<size_t> nodes_order;
    nodes_order.reserve(csr_nodes.size());

    std::queue<size_t> bfs_queue;
    bfs_queue.push(from);
    while (!bfs_queue.empty()) {
        const auto i_node = bfs_queue.front();
        bfs_queue.pop();
        for (const auto& neighbor : get_neighbors(i_node)) {
            nodes_order.emplace_back(neighbor);
            bfs_queue.push(neighbor);
        }
    }

    return nodes_order;
}

NeighborRange<size_t> CSRGraph::get_neighbors(const size_t node) noexcept {
    return NeighborRange(&edges[offsets[node]], &edges[offsets[node + 1]]);
}

NeighborRange<size_t> CSRGraph::get_predecessors(const size_t node) noexcept {
    return NeighborRange(&edges_predecessors[offsets_predecessors[node]],
                         &edges_predecessors[offsets_predecessors[node + 1]]);
}
