#pragma once
#include <filesystem>
#include <vector>

#include "data_structures/CSRGraph.hpp"
#include "language_processing/types/Token.hpp"

class LogicGateLanguage {
public:
    LogicGateLanguage();
    explicit LogicGateLanguage(std::filesystem::path program_file);
    explicit LogicGateLanguage(std::filesystem::path program_file, std::filesystem::path output_file);

    int execute();
    void create_graph();
    void execute_cycle();
    void register_output();

private:
    std::filesystem::path program_file;
    std::filesystem::path output_file;
    std::vector<Token> tokens;
    CSRGraph graph_csr;
};
