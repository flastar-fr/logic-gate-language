#pragma once
#include "Token.hpp"

void verify_token_type(const Token& token, const TokenType& node_type);
void verify_token_identifier(const Token& token, const std::string& identifier_value);
