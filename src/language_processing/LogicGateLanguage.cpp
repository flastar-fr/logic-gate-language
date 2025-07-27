#include "LogicGateLanguage.hpp"

#include <iostream>

#include "data_structures/CSRGraph.hpp"
#include "parser/Parser.hpp"
#include "preprocessor/Preprocessor.hpp"
#include "scanner/Scanner.hpp"
#include "utils/io_manipulation.hpp"

LogicGateLanguage::LogicGateLanguage(std::string program_file) : program_file(std::move(program_file)) {}

int LogicGateLanguage::execute() {
    std::vector<std::string> program;

    const bool is_open = read_file(program_file, program);
    if (!is_open) {
        return 2;
    }

    auto scanner = Scanner(program);
    tokens = scanner.scan();

    auto preprocessor = Preprocessor(tokens);
    tokens = preprocessor.preprocess();

    create_graph();

    return 0;
}

void LogicGateLanguage::create_graph() const {
    auto parser = Parser(tokens);
    const auto graph = parser.parse();
    graph.print_graph();

    std::cout << std::endl;
    std::cout << "Execution:" << std::endl;
    auto graph_csr = CSRGraph(graph);
    graph_csr.propagate();
    graph_csr.print_states();
}
