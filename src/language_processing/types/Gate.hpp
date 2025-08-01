#pragma once
#include <string>
#include <utility>

#include "utils/error_messages.hpp"

struct Gate {
    Gate() = default;

    Gate(const std::unordered_map<std::string, size_t>& inputs, const std::unordered_map<std::string, size_t>& outputs,
         const bool prerendered): inputs(inputs), outputs(outputs), prerendered(prerendered) {
        for (const auto& [key, value] : inputs) {
            inputs_order.push_back(key);
        }
        for (const auto& [key, value] : outputs) {
            outputs_order.push_back(key);
        }
    }

    Gate(const std::unordered_map<std::string, size_t>& inputs, const std::unordered_map<std::string, size_t>& outputs,
         const uint32_t table,
         const bool prerendered) : inputs(inputs), outputs(outputs), table(table), prerendered(prerendered) {
        for (const auto& [key, value] : inputs) {
            inputs_order.push_back(key);
        }
        for (const auto& [key, value] : outputs) {
            outputs_order.push_back(key);
        }
    }

    Gate(const std::unordered_map<std::string, size_t>& inputs, const std::unordered_map<std::string, size_t>& outputs,
         Graph graph,
         const bool prerendered) : inputs(inputs), outputs(outputs), graph(std::move(graph)),
                                   prerendered(prerendered) {
        for (const auto& [key, value] : inputs) {
            inputs_order.push_back(key);
        }
        for (const auto& [key, value] : outputs) {
            outputs_order.push_back(key);
        }
    }

    Gate(const std::vector<std::string>& inputs_vector, const std::vector<std::string>& outputs_vector,
         const uint32_t table, const bool prerendered) : inputs_order(inputs_vector), outputs_order(outputs_vector),
                                                         table(table), prerendered(prerendered) {
        for (const auto& input : inputs_vector) {
            inputs[input] = -1;
        }
        for (const auto& output : outputs_vector) {
            outputs[output] = -1;
        }
    }

    Gate(const std::vector<std::string>& inputs_vector, const std::vector<std::string>& outputs_vector, Graph graph,
         const bool prerendered) : inputs_order(inputs_vector), outputs_order(outputs_vector), graph(std::move(graph)),
                                   prerendered(prerendered) {
        for (const auto& input : inputs_vector) {
            inputs[input] = -1;
        }
        for (const auto& output : outputs_vector) {
            outputs[output] = -1;
        }
    }

    void add_input(const std::string& input, const size_t index) {
        inputs[input] = index;
        inputs_order.push_back(input);
    }

    void add_output(const std::string& output, const size_t index) {
        outputs[output] = index;
        outputs_order.push_back(output);
    }

    std::unordered_map<std::string, size_t> inputs;
    std::unordered_map<std::string, size_t> outputs;
    std::vector<std::string> inputs_order;
    std::vector<std::string> outputs_order;
    uint32_t table = 0;
    Graph graph;
    bool prerendered = false;
};

inline size_t get_gate_index_node(const std::string& node_identifier, const Gate& gate) {
    if (gate.inputs.count(node_identifier)) {
        return gate.inputs.at(node_identifier);
    }
    if (gate.outputs.count(node_identifier)) {
        return gate.outputs.at(node_identifier);
    }

    throw_invalid_argument_error("Node not found : " + node_identifier);
    return -1;
}
