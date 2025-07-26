#include <string>
#include <gtest/gtest.h>

#include "language_processing/scanner/Scanner.hpp"

TEST(ScannerTest, IncludeDefinition) {
    const std::vector expected_tokens = {
        Token(TokenType::HASHTAG),
        Token(TokenType::IDENTIFIER, "include"),
        Token(TokenType::STRING, "xor.lg"),
        Token(TokenType::EOL)
    };
    const std::string string_to_test = "#include \"xor.lg\"";

    auto scanner = Scanner({string_to_test});
    const auto tokens = scanner.scan();

    EXPECT_EQ(expected_tokens, tokens);
}

TEST(ScannerTest, IdentifiersSeparatedByKeycharAndSpace) {
    const std::vector expected_tokens = {
        Token(TokenType::IDENTIFIER, "op1"),
        Token(TokenType::COMMA),
        Token(TokenType::IDENTIFIER, "op2"),
        Token(TokenType::EOL)
    };
    const std::string string_to_test = "op1, op2";

    auto scanner = Scanner({string_to_test});
    const auto tokens = scanner.scan();

    EXPECT_EQ(expected_tokens, tokens);
}

TEST(ScannerTest, IdentifiersSeparatedByKeychar) {
    const std::vector expected_tokens = {
        Token(TokenType::IDENTIFIER, "b"),
        Token(TokenType::DOT),
        Token(TokenType::IDENTIFIER, "out"),
        Token(TokenType::EOL)
    };
    const std::string string_to_test = "b.out";

    auto scanner = Scanner({string_to_test});
    const auto tokens = scanner.scan();

    EXPECT_EQ(expected_tokens, tokens);
}

TEST(ScannerTest, ComplexeIdentifiersMixedKeychars) {
    const std::vector expected_tokens = {
        Token(TokenType::IDENTIFIER, "input"),
        Token(TokenType::COLON),
        Token(TokenType::IDENTIFIER, "op1"),
        Token(TokenType::COMMA),
        Token(TokenType::IDENTIFIER, "op2"),
        Token(TokenType::EOL)
    };
    const std::string string_to_test = "input : op1, op2";

    auto scanner = Scanner({string_to_test});
    const auto tokens = scanner.scan();

    EXPECT_EQ(expected_tokens, tokens);
}

TEST(ScannerTest, ComplexeBooleansMixedKeychars) {
    const std::vector expected_tokens = {
        Token(TokenType::LEFT_PAREN),
        Token(TokenType::BOOLEAN, "1"),
        Token(TokenType::COMMA),
        Token(TokenType::BOOLEAN, "1"),
        Token(TokenType::COMMA),
        Token(TokenType::BOOLEAN, "false"),
        Token(TokenType::PIPE),
        Token(TokenType::BOOLEAN, "1"),
        Token(TokenType::COMMA),
        Token(TokenType::BOOLEAN, "true"),
        Token(TokenType::RIGHT_PAREN),
        Token(TokenType::EOL)
    };
    const std::string string_to_test = "(1, 1, false | 1, true)";

    auto scanner = Scanner({string_to_test});
    const auto tokens = scanner.scan();

    EXPECT_EQ(expected_tokens, tokens);
}

TEST(ScannerTest, StructDefinition) {
    const std::vector expected_tokens = {
        Token(TokenType::IDENTIFIER, "struct"),
        Token(TokenType::IDENTIFIER, "or"),
        Token(TokenType::LEFT_BRACE),
        Token(TokenType::EOL)
    };
    const std::string string_to_test = "struct or {";

    auto scanner = Scanner({string_to_test});
    const auto tokens = scanner.scan();

    EXPECT_EQ(expected_tokens, tokens);
}
