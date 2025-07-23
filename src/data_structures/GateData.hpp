#pragma once
#include "GateRenderType.hpp"
#include "TruthTable.hpp"

struct GateData {
    GateData() = default;
    GateData(const TruthTable truth_table, GateRenderType render_type): truth_table(truth_table), render_type(render_type) {}

    TruthTable truth_table;
    GateRenderType render_type;
};
