#include <bitset>
#include <gtest/gtest.h>

#include "data_structures/CSRGraph.hpp"

CSRGraph construct_gate_from_truth_table(uint32_t truth_table) {
    auto node0 = Node(0, NodeType::INPUT);
    node0.state = true;
    auto node1 = Node(1, NodeType::INPUT);
    node1.state = true;
    auto node2 = Node(2, NodeType::GATE);
    node2.gate_data = GateData(truth_table, 2, GateRenderType::PRERENDERED);
    auto node3 = Node(3, NodeType::GATE_OUTPUT);
    auto node4 = Node(4, NodeType::GATE_OUTPUT);
    auto node5 = Node(5, NodeType::OUTPUT);
    auto node6 = Node(6, NodeType::OUTPUT);
    auto graph = Graph(7);
    graph.add_edge(node0, node2);
    graph.add_edge(node1, node2);
    graph.add_edge(node2, node3);
    graph.add_edge(node2, node4);
    graph.add_edge(node3, node5);
    graph.add_edge(node4, node6);

    auto graph_csr = CSRGraph(graph);

    return graph_csr;
}

TEST(CSRGraphTest, ExecuteGatePrerenderedPropagation1Output) {
    constexpr uint32_t test_truth_table = 0b1000;

    auto node0 = Node(0, NodeType::INPUT);
    node0.state = true;
    auto node1 = Node(1, NodeType::INPUT);
    node1.state = true;
    auto node2 = Node(2, NodeType::GATE);
    node2.gate_data = GateData(test_truth_table, 1, GateRenderType::PRERENDERED);
    auto node3 = Node(3, NodeType::GATE_OUTPUT);
    auto graph = Graph(4);
    graph.add_edge(node0, node2);
    graph.add_edge(node1, node2);
    graph.add_edge(node2, node3);

    auto graph_csr = CSRGraph(graph);
    const auto& nodes = graph_csr.get_csr_nodes();
    const auto neighbors = graph_csr.get_neighbors(2);
    const auto predecessors = graph_csr.get_predecessors(2);
    graph_csr.execute_gate_prerendered_propagation(nodes[2], predecessors, neighbors);

    EXPECT_TRUE(nodes[3].state);
}

TEST(CSRGraphTest, ExecuteGatePrerenderedPropagation2Outputs) {
    constexpr uint32_t test_truth_table = 0b0010'1001;

    auto node0 = Node(0, NodeType::INPUT);
    node0.state = true;
    auto node1 = Node(1, NodeType::INPUT);
    node1.state = false;
    auto node2 = Node(2, NodeType::GATE);
    node2.gate_data = GateData(test_truth_table, 2, GateRenderType::PRERENDERED);
    auto node3 = Node(3, NodeType::GATE_OUTPUT);
    auto node4 = Node(4, NodeType::GATE_OUTPUT);
    auto graph = Graph(5);
    graph.add_edge(node0, node2);
    graph.add_edge(node1, node2);
    graph.add_edge(node2, node3);
    graph.add_edge(node2, node4);

    auto graph_csr = CSRGraph(graph);
    const auto& nodes = graph_csr.get_csr_nodes();
    const auto neighbors = graph_csr.get_neighbors(2);
    const auto predecessors = graph_csr.get_predecessors(2);
    graph_csr.execute_gate_prerendered_propagation(nodes[2], predecessors, neighbors);

    EXPECT_FALSE(nodes[3].state);
    EXPECT_TRUE(nodes[4].state);
}

TEST(CSRGraphTest, DetermineGraphGateDataNormalValue) {
    constexpr uint32_t test_truth_table = 0b1000'0001;
    auto graph_csr = construct_gate_from_truth_table(test_truth_table);

    const auto gate_data = graph_csr.determine_graph_gate_data();

    EXPECT_EQ(test_truth_table, gate_data.truth_table);
}

TEST(CSRGraphTest, DetermineGraphGateDataNormalValue2) {
    constexpr uint32_t test_truth_table = 0b0010'1001;
    auto graph_csr = construct_gate_from_truth_table(test_truth_table);

    const auto gate_data = graph_csr.determine_graph_gate_data();

    EXPECT_EQ(test_truth_table, gate_data.truth_table);
}

TEST(CSRGraphTest, SetInputsFromValue2Inputs) {
    auto node0 = Node(0, NodeType::INPUT);
    auto node1 = Node(1, NodeType::INPUT);

    auto graph = Graph(2);
    graph.add_edge(node0, node1);

    auto graph_csr = CSRGraph(graph);
    graph_csr.set_inputs_with_value(0b10);

    const auto& nodes = graph_csr.get_csr_nodes();
    const auto& inputs = graph_csr.get_inputs();

    EXPECT_FALSE(nodes[inputs[0]].state);
    EXPECT_TRUE(nodes[inputs[1]].state);
}

TEST(CSRGraphTest, SetInputsFromValue3Inputs) {
    auto node0 = Node(0, NodeType::INPUT);
    auto node1 = Node(1, NodeType::INPUT);
    auto node2 = Node(2, NodeType::INPUT);

    auto graph = Graph(3);
    graph.add_edge(node0, node1);
    graph.add_edge(node1, node2);

    auto graph_csr = CSRGraph(graph);
    graph_csr.set_inputs_with_value(0b101);

    const auto& nodes = graph_csr.get_csr_nodes();
    const auto& inputs = graph_csr.get_inputs();

    EXPECT_TRUE(nodes[inputs[0]].state);
    EXPECT_FALSE(nodes[inputs[1]].state);
    EXPECT_TRUE(nodes[inputs[2]].state);
}
