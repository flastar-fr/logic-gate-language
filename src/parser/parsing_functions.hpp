#pragma once
#include <string>
#include <vector>

#include "Token.hpp"

void parse_line(std::string& line, std::vector<Token>& tokens);
std::vector<Token> parse_lines(std::vector<std::string>& lines);
