#include <gtest/gtest.h>

#include "language_processing/preprocessor/Preprocessor.hpp"


TEST(PreprocessorTest, RemoveCommentsIdentifier) {
    const std::vector expected_tokens = {
        Token(TokenType::IDENTIFIER, "test"),
        Token(TokenType::IDENTIFIER, "end"),
    };

    const std::vector tokens = {
        Token(TokenType::IDENTIFIER, "test"),
        Token(TokenType::DOUBLE_SLASH),
        Token(TokenType::IDENTIFIER, "comment"),
        Token(TokenType::EOL),
        Token(TokenType::IDENTIFIER, "end"),
    };

    auto preprocessor = Preprocessor(tokens);
    preprocessor.remove_comments();

    EXPECT_EQ(expected_tokens, preprocessor.get_tokens());
}

TEST(PreprocessorTest, RemoveCommentsString) {
    const std::vector expected_tokens = {
        Token(TokenType::IDENTIFIER, "test"),
        Token(TokenType::IDENTIFIER, "end"),
    };

    const std::vector tokens = {
        Token(TokenType::IDENTIFIER, "test"),
        Token(TokenType::DOUBLE_SLASH),
        Token(TokenType::STRING, "comment"),
        Token(TokenType::EOL),
        Token(TokenType::IDENTIFIER, "end"),
    };

    auto preprocessor = Preprocessor(tokens);
    preprocessor.remove_comments();

    EXPECT_EQ(expected_tokens, preprocessor.get_tokens());
}
