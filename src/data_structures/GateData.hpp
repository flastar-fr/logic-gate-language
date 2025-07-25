#pragma once
#include <cstdint>

#include "GateRenderType.hpp"

struct GateData {
    GateData() = default;

    GateData(const uint8_t truth_table, const uint8_t amount_outputs, const GateRenderType render_type): render_type(render_type),
                                                                           truth_table(truth_table), amount_outputs(amount_outputs) {}


    GateRenderType render_type;
    uint32_t truth_table;
    uint8_t amount_outputs;
};
