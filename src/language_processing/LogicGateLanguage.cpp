#include "LogicGateLanguage.hpp"

#include <iostream>

#include "language_processing/parser/Parser.hpp"
#include "language_processing/preprocessor/Preprocessor.hpp"
#include "language_processing/scanner/Scanner.hpp"
#include "utils/io_manipulation.hpp"

LogicGateLanguage::LogicGateLanguage(const std::string& program_file) : program_file(program_file), graph_csr({}) {}

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
    }
}

void LogicGateLanguage::execute_cycle() {
    std::cout << "Execution:" << std::endl;
    graph_csr.propagate();
    graph_csr.print_states();
}
