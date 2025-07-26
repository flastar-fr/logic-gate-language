#pragma once
#include <vector>

#include "language_processing/Token.hpp"

class Preprocessor {
public:
    explicit Preprocessor(const std::vector<Token>& tokens);

    std::vector<Token>& preprocess();
    void remove_comments();
    [[nodiscard]] const std::vector<Token>& get_tokens() const { return tokens; }

private:
    std::vector<Token> tokens;
};
