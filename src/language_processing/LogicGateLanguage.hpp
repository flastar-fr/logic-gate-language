#pragma once
#include <vector>

#include "Token.hpp"

class LogicGateLanguage {
public:
    explicit LogicGateLanguage(const std::string& program_file);

    int execute();
    void create_graph();

private:
    std::string program_file;
    std::vector<Token> tokens;
};
