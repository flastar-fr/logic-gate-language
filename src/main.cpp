#include <iostream>

#include "language_processing/LogicGateLanguage.hpp"

int main(const int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "No inputed file" << std::endl;
        return 1;
    }

    auto language_program = LogicGateLanguage(std::string(argv[1]));

    return language_program.execute();
}
