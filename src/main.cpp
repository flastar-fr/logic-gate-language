#include <iostream>

#include "data_structures/CSRGraph.hpp"
#include "data_structures/Graph.hpp"

int main() {
    std::cout << "Graph" << std::endl;
    auto graph = Graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(0, 3);
    graph.add_edge(1, 3);
    graph.add_edge(2, 0);
    graph.add_edge(3, 1);
    graph.add_edge(3, 2);
    graph.add_edge(2, 3);
    graph.print_graph();

    std::cout << "Graph CSR" << std::endl;
    const auto graph_csr = CSRGraph(graph);
    graph_csr.print_graph();

    return 0;
}
