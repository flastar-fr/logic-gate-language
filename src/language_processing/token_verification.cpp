#include "token_verification.hpp"

#include "utils/error_messages.hpp"

void verify_token_type(const Token& token, const TokenType& node_type) {
    if (token.type != node_type) {
        throw_invalid_argument_error("Invalid " + tostring(token.type) + ". Expected " + tostring(node_type));
    }
}

void verify_token_identifier(const Token& token, const std::string& identifier_value) {
    constexpr auto identifier_type = TokenType::IDENTIFIER;
    if (token.type != identifier_type) {
        throw_invalid_argument_error("Invalid " + tostring(token.type) + ". Expected " + tostring(identifier_type));
    }
    if (token.value != identifier_value) {
        throw_invalid_argument_error("Invalid " + identifier_value + ". Expected " + identifier_value);
    }
}
