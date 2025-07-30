#pragma once
#include <string>
#include <utility>

#include "utils/error_messages.hpp"

struct Gate {
    Gate() = default;

    Gate(const std::vector<std::string>& inputs, const std::vector<std::string>& outputs,
         const bool prerendered): inputs(inputs), outputs(outputs), prerendered(prerendered) {}

    Gate(const std::vector<std::string>& inputs, const std::vector<std::string>& outputs, const uint32_t table,
         const bool prerendered) : inputs(inputs), outputs(outputs), table(table), prerendered(prerendered) {}

    Gate(const std::vector<std::string>& inputs, const std::vector<std::string>& outputs, Graph graph,
         const bool prerendered) : inputs(inputs), outputs(outputs), graph(std::move(graph)),
                                   prerendered(prerendered) {}

    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
    uint32_t table = 0;
    Graph graph;
    bool prerendered = false;
};

inline size_t get_gate_index_node(const std::string& node_identifier, const Gate& gate) {
    for (size_t i = 0; i < gate.inputs.size(); ++i) {
        if (gate.inputs[i] == node_identifier) {
            return i;
        }
    }

    for (size_t i = 0; i < gate.outputs.size(); ++i) {
        if (gate.outputs[i] == node_identifier) {
            return gate.inputs.size() + i;
        }
    }

    throw_invalid_argument_error("Node not found : " + node_identifier);
    return -1;
}

