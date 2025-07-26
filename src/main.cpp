#include <iostream>

#include "language_processing/preprocessor/Preprocessor.hpp"
#include "language_processing/scanner/Scanner.hpp"
#include "utils/io_manipulation.hpp"

int main(const int argc, char* argv[]) {
    std::vector<std::string> program;
    if (argc < 2) {
        std::cerr << "No inputed file" << std::endl;
        return 1;
    }

    const bool is_open = read_file(std::string(argv[1]), program);
    if (!is_open) {
        return 2;
    }

    auto scanner = Scanner(program);
    const auto tokens = scanner.scan();

    std::cout << "Scanner : " << tokens.size() << std::endl;
    for (const auto& token : tokens) {
        std::cout << token << std::endl;
    }

    auto preprocessor = Preprocessor(tokens);
    const auto preprocessed_tokens = preprocessor.preprocess();

    std::cout << std::endl;
    std::cout << "Preprocessor : " << preprocessed_tokens.size() << std::endl;
    for (const auto& token : preprocessed_tokens) {
        std::cout << token << std::endl;
    }

    return 0;
}
