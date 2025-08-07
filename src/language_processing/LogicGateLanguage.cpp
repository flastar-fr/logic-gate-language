#include "LogicGateLanguage.hpp"

#include <fstream>
#include <iostream>
#include <utility>

#include "language_processing/parser/Parser.hpp"
#include "language_processing/preprocessor/Preprocessor.hpp"
#include "language_processing/scanner/Scanner.hpp"
#include "utils/io_manipulation.hpp"

LogicGateLanguage::LogicGateLanguage() : graph_csr({}) {}

LogicGateLanguage::LogicGateLanguage(std::filesystem::path program_file) : program_file(std::move(program_file)),
                                                                           graph_csr({}) {}

LogicGateLanguage::LogicGateLanguage(std::filesystem::path program_file, std::filesystem::path output_file) :
    program_file(std::move(program_file)), output_file(std::move(output_file)), graph_csr({}) {}

int LogicGateLanguage::execute() {
    std::vector<std::string> program;

    const bool is_open = read_file(program_file, program);
    if (!is_open) {
        return 2;
    }

    auto preprocessor = Preprocessor(program, program_file.parent_path(), program_file);
    const auto lines = preprocessor.preprocess();

    auto scanner = Scanner(lines);
    tokens = scanner.scan();

    create_graph();

    return 0;
}

void LogicGateLanguage::create_graph() {
    auto parser = Parser(tokens);
    const auto graph = parser.parse();
    graph.print_graph();
    graph_csr = CSRGraph(graph);

    std::cout << std::endl;
    execute_cycle();

    for (const auto input : parser.get_read_inputs()) {
        graph_csr.set_inputs_with_value(input);
        std::cout << std::endl;
        execute_cycle();
        if (!output_file.empty()) register_output();
    }
}

void LogicGateLanguage::execute_cycle() {
    std::cout << "Execution:" << std::endl;
    graph_csr.propagate();
    graph_csr.print_states();
}

void LogicGateLanguage::register_output() {
    const auto& nodes = graph_csr.get_csr_nodes();
    auto file = std::ofstream(output_file);
    if (!file.is_open()) throw_invalid_argument_error("Cannot open file " + output_file.string());
    for (const auto output : graph_csr.get_outputs()) {
        const bool node_state = nodes[output].state;
        file << node_state;
    }
    file.close();
}
