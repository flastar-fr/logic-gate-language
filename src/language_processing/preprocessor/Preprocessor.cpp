#include "Preprocessor.hpp"

Preprocessor::Preprocessor(const std::vector<Token>& tokens) : tokens(tokens) {}

std::vector<Token>& Preprocessor::preprocess() {
    remove_comments();
    process_includes();
    remove_eols();

    return tokens;
}

void Preprocessor::remove_comments() {
    std::vector<Token> new_tokens;
    new_tokens.reserve(tokens.size());

    bool is_comment = false;
    for (const auto& token : tokens) {
        if (token.type == TokenType::DOUBLE_SLASH) is_comment = true;

        if (!is_comment) {
            new_tokens.push_back(token);
        }

        if (token.type == TokenType::EOL && is_comment) is_comment = false;
    }

    tokens = new_tokens;
}

void Preprocessor::process_includes() {
    // TODO :
}

void Preprocessor::remove_eols() {
    std::vector<Token> new_tokens;
    new_tokens.reserve(tokens.size());

    for (const auto& token : tokens) {
        if (token.type != TokenType::EOL) new_tokens.push_back(token);
    }

    tokens = new_tokens;
}
