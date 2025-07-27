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

TEST(PreprocessorTest, RemoveEOLs) {
    const std::vector expected_tokens = {
        Token(TokenType::IDENTIFIER, "struct"),
        Token(TokenType::IDENTIFIER, "and"),
        Token(TokenType::LEFT_BRACE, ""),
        Token(TokenType::IDENTIFIER, "input"),
        Token(TokenType::COLON, ""),
        Token(TokenType::IDENTIFIER, "op1"),
        Token(TokenType::COMMA, ""),
        Token(TokenType::IDENTIFIER, "op2"),
        Token(TokenType::SEMICOLON, ""),
        Token(TokenType::IDENTIFIER, "output"),
        Token(TokenType::COLON, ""),
        Token(TokenType::IDENTIFIER, "out"),
        Token(TokenType::SEMICOLON, ""),
        Token(TokenType::IDENTIFIER, "circuit"),
        Token(TokenType::COLON, ""),
        Token(TokenType::LEFT_BRACE, ""),
        Token(TokenType::RIGHT_BRACE, ""),
        Token(TokenType::SEMICOLON, ""),
        Token(TokenType::RIGHT_BRACE, "")
    };

    const std::vector tokens = {
        Token(TokenType::IDENTIFIER, "struct"),
        Token(TokenType::IDENTIFIER, "and"),
        Token(TokenType::LEFT_BRACE, ""),
        Token(TokenType::EOL, ""),
        Token(TokenType::IDENTIFIER, "input"),
        Token(TokenType::COLON, ""),
        Token(TokenType::IDENTIFIER, "op1"),
        Token(TokenType::COMMA, ""),
        Token(TokenType::IDENTIFIER, "op2"),
        Token(TokenType::SEMICOLON, ""),
        Token(TokenType::EOL, ""),
        Token(TokenType::IDENTIFIER, "output"),
        Token(TokenType::COLON, ""),
        Token(TokenType::IDENTIFIER, "out"),
        Token(TokenType::SEMICOLON, ""),
        Token(TokenType::EOL, ""),
        Token(TokenType::IDENTIFIER, "circuit"),
        Token(TokenType::COLON, ""),
        Token(TokenType::LEFT_BRACE, ""),
        Token(TokenType::EOL, ""),
        Token(TokenType::EOL, ""),
        Token(TokenType::RIGHT_BRACE, ""),
        Token(TokenType::SEMICOLON, ""),
        Token(TokenType::EOL, ""),
        Token(TokenType::RIGHT_BRACE, "")
    };

    auto preprocessor = Preprocessor(tokens);
    preprocessor.remove_eols();

    EXPECT_EQ(expected_tokens, preprocessor.get_tokens());
}
