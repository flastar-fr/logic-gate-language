#pragma once
#include <filesystem>
#include <vector>

#include "data_structures/CSRGraph.hpp"
#include "language_processing/types/Token.hpp"

class LogicGateLanguage {
public:
    explicit LogicGateLanguage(const std::string& program_file);

    int execute();
    void create_graph();
    void execute_cycle();

private:
    std::filesystem::path program_file;
    std::vector<Token> tokens;
    CSRGraph graph_csr;
};
