#include <iostream>

#include "language_processing/LogicGateLanguage.hpp"
#include "utils/error_messages.hpp"

int main(const int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "No inputed file" << std::endl;
        return 1;
    }

    LogicGateLanguage language_program;
    if (argc == 2) language_program = LogicGateLanguage(std::string(argv[1]));
    else if (argc == 3) language_program = LogicGateLanguage(std::string(argv[1]), std::string(argv[2]));
    else throw_invalid_argument_error("Invalid program arguments");

    return language_program.execute();
}
