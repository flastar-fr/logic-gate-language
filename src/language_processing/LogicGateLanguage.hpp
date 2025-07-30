#pragma once
#include <vector>

#include "language_processing/types/Token.hpp"

class LogicGateLanguage {
public:
    explicit LogicGateLanguage(std::string program_file);

    int execute();
    void create_graph() const;

private:
    std::string program_file;
    std::vector<Token> tokens;
};
