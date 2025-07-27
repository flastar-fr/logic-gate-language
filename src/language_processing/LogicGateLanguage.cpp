#include "LogicGateLanguage.hpp"

#include <iostream>

#include "preprocessor/Preprocessor.hpp"
#include "scanner/Scanner.hpp"
#include "utils/io_manipulation.hpp"

LogicGateLanguage::LogicGateLanguage(const std::string& program_file) : program_file(program_file) {}

int LogicGateLanguage::execute() {
    std::vector<std::string> program;

    const bool is_open = read_file(program_file, program);
    if (!is_open) {
        return 2;
    }

    auto scanner = Scanner(program);
    tokens = scanner.scan();

    std::cout << "Scanner : " << tokens.size() << std::endl;
    for (const auto& token : tokens) {
        std::cout << token << std::endl;
    }

    auto preprocessor = Preprocessor(tokens);
    tokens = preprocessor.preprocess();

    std::cout << std::endl;
    std::cout << "Preprocessor : " << tokens.size() << std::endl;
    for (const auto& token : tokens) {
        std::cout << token << std::endl;
    }

    create_graph();

    return 0;
}

void LogicGateLanguage::create_graph() {

}
