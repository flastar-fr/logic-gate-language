#include "Scanner.hpp"

#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "utils/error_messages.hpp"

const auto EOL_TOKEN = Token(TokenType::EOL);

const std::unordered_map<std::string, TokenType> KEYCHARS = {
    {"#", TokenType::HASHTAG},
    {"(", TokenType::LEFT_PAREN},
    {")", TokenType::RIGHT_PAREN},
    {"{", TokenType::LEFT_BRACE},
    {"}", TokenType::RIGHT_BRACE},
    {",", TokenType::COMMA},
    {":", TokenType::COLON},
    {".", TokenType::DOT},
    {"=", TokenType::EQUAL},
    {"|", TokenType::PIPE},
    {";", TokenType::SEMICOLON},
    {"->", TokenType::RIGHT_ARROW},
    {"//", TokenType::DOUBLE_SLASH}
};

const std::unordered_set<std::string> BOOLEAN_VALUES = {"true", "false", "1", "0"};

constexpr char QUOTE_CHAR = '"';

bool is_keychar(const std::string& token_to_test) {
    return KEYCHARS.count(token_to_test);
}

Scanner::Scanner(const std::vector<std::string>& program) : program(program) {}

std::vector<Token> Scanner::scan() {
    for (const auto& line : program) {
        scan_line(line);
        ++current_line;
    }
    return tokens;
}

void Scanner::scan_line(const std::string& line) {
    for (const auto char_token : line) {
        if (char_token == QUOTE_CHAR) are_double_quotes_open = !are_double_quotes_open;
        if (is_keychar(std::string(1, char_token)) && !current_token.empty()) {
            check_literal();
        }
        append_or_finalize_token(char_token);
    }

    check_token();
    check_literal();

    if (!current_token.empty() || are_double_quotes_open) {
        throw_invalid_argument_error("Unrecognized token: " + current_token);
    }
}

void Scanner::check_token() {
    if (!is_keychar(current_token) || are_double_quotes_open) return;
    add_token(Token(KEYCHARS.at(current_token), current_line));
}

void Scanner::check_literal() {
    if (current_token.empty() || are_double_quotes_open) return;

    if (current_token[0] == QUOTE_CHAR && current_token[current_token.size() - 1] == QUOTE_CHAR) {
        add_token(Token(TokenType::STRING, current_token.substr(1, current_token.size() - 2), current_line));
        return;
    }
    if (BOOLEAN_VALUES.count(current_token)) {
        add_token(Token(TokenType::BOOLEAN, current_token, current_line));
        return;
    }
    add_token(Token(TokenType::IDENTIFIER, current_token, current_line));
}

void Scanner::add_token(const Token& token) {
    tokens.push_back(token);
    current_token.clear();
}

void Scanner::append_or_finalize_token(const std::string::value_type char_token) {
    if (char_token == ' ') {
        check_literal();
        return;
    }

    current_token.push_back(char_token);
    check_token();
}
