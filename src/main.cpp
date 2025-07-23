#include <iostream>

#include "data_structures/CSRGraph.hpp"
#include "data_structures/Graph.hpp"

int main() {
    std::cout << "Graph 3 nodes" << std::endl;
    std::cout << "Graph" << std::endl;
    auto node0 = Node(0, NodeType::INPUT);
    node0.state = true;
    auto node1 = Node(1, NodeType::NODE_WIRE);
    auto node2 = Node(2, NodeType::OUTPUT);
    auto graph = Graph(3);
    graph.add_edge(node0, node1);
    graph.add_edge(node1, node2);
    graph.print_graph();

    std::cout << std::endl;
    std::cout << "Graph CSR" << std::endl;
    auto graph_csr = CSRGraph(graph);
    graph_csr.print_graph();

    std::cout << std::endl;
    std::cout << "Result" << std::endl;
    graph_csr.process();
    graph_csr.print_process();

    std::cout << std::endl;
    std::cout << "Graph 2 nodes" << std::endl;
    std::cout << "Graph" << std::endl;
    node0 = Node(0, NodeType::INPUT);
    node0.state = true;
    node1 = Node(1, NodeType::OUTPUT);
    graph = Graph(2);
    graph.add_edge(node0, node1);
    graph.print_graph();

    std::cout << std::endl;
    std::cout << "Graph CSR" << std::endl;
    graph_csr = CSRGraph(graph);
    graph_csr.print_graph();

    std::cout << std::endl;
    std::cout << "Result" << std::endl;
    graph_csr.process();
    graph_csr.print_process();

    std::cout << std::endl;
    std::cout << "Graph multiple nodes" << std::endl;
    std::cout << "Graph" << std::endl;
    node0 = Node(0, NodeType::UNDEFINED);
    node1 = Node(1, NodeType::UNDEFINED);
    node2 = Node(2, NodeType::UNDEFINED);
    auto node3 = Node(3, NodeType::UNDEFINED);
    graph = Graph(0);
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
    graph_csr = CSRGraph(graph);
    graph_csr.print_graph();

    return 0;
}
