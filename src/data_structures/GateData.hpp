#pragma once
#include <cstdint>

#include "GateRenderType.hpp"

struct GateData {
    GateData() = default;

    GateData(const uint8_t truth_table, const GateRenderType render_type): render_type(render_type),
                                                                           truth_table(truth_table) {}


    GateRenderType render_type;
    uint8_t truth_table;
};
