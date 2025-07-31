#pragma once
#include <unordered_map>

#include "language_processing/types/Gate.hpp"

const auto and_gate = Gate({"op1", "op2"}, {"out"}, 0b1000, true);
const auto or_gate = Gate({"op1", "op2"}, {"out"}, 0b1110, true);
const auto not_gate = Gate({"in"}, {"out"}, 0b01, true);

const std::unordered_map<std::string, Gate> DEFAULT_GATES = {
    {"and", and_gate},
    {"or", or_gate},
    {"not", not_gate}
};
