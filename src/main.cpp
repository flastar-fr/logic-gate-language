#include <iostream>

#include "data_structures/CSRGraph.hpp"
#include "data_structures/Graph.hpp"

int main() {
    std::cout << "Graph" << std::endl;
    auto node0 = Node(0, NodeType::UNDEFINED);
    auto node1 = Node(1, NodeType::UNDEFINED);
    auto node2 = Node(2, NodeType::UNDEFINED);
    auto node3 = Node(3, NodeType::UNDEFINED);
    auto graph = Graph(0);
    graph.add_edge(node0, node1);
    graph.add_edge(node0, node2);
    graph.add_edge(node0, node3);
    graph.add_edge(node1, node3);
    graph.add_edge(node2, node0);
    graph.add_edge(node2, node3);
    graph.add_edge(node3, node1);
    graph.add_edge(node3, node2);
    graph.print_graph();

    std::cout << "Graph CSR" << std::endl;
    const auto graph_csr = CSRGraph(graph);
    graph_csr.print_graph();

    return 0;
}
