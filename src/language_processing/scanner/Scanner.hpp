#pragma once
#include <string>
#include <vector>

#include "language_processing/Token.hpp"

class Scanner {
public:
    explicit Scanner(const std::vector<std::string>& program);

    std::vector<Token> scan();
    void scan_line(const std::string& line);
    void check_token();
    void check_literal();
    void add_token(const Token& token);
    void append_or_finalize_token(std::string::value_type char_token);

private:
    std::vector<std::string> program;
    std::vector<Token> tokens;
    std::string current_token;
    bool are_double_quotes_open = false;
};
