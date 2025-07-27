#pragma once
#include <set>
#include <string>

struct Gate {
    Gate(const std::set<std::string>& inputs, const std::set<std::string>& outputs): inputs(inputs), outputs(outputs) {}
    Gate(const std::set<std::string>& inputs, const std::set<std::string>& outputs,
        const uint32_t table) : inputs(inputs), outputs(outputs), table(table) {}

    std::set<std::string> inputs;
    std::set<std::string> outputs;
    uint32_t table = 0;
};
