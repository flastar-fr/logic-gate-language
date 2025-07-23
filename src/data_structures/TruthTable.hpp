#pragma once
#include <cstdint>

struct TruthTable {
    TruthTable() = default;
    TruthTable(const uint8_t truth_table, const uint8_t amount_operands): truth_table(truth_table), amount_operands(amount_operands) {}

    uint8_t truth_table = 0;
    uint8_t amount_operands = 0;
};
