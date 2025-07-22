#include <iostream>

#include "data_structures/CSRGraph.hpp"
#include "data_structures/Graph.hpp"

int main() {
    std::cout << "Graph" << std::endl;
    auto node0 = Node(0, NodeType::INPUT);
    node0.state = true;
    auto node1 = Node(1, NodeType::OUTPUT);
    auto graph = Graph(2);
    graph.add_edge(node0, node1);
    graph.print_graph();

    std::cout << "Graph CSR" << std::endl;
    const auto graph_csr = CSRGraph(graph);
    graph_csr.print_graph();

    return 0;
}
