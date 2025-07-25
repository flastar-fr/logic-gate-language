#pragma once
#include <ostream>
#include <string>

#include "TokenType.hpp"

struct Token {
    explicit Token(const TokenType type) : type(type) {}
    explicit Token(const TokenType type, const std::string& value) : type(type), value(value) {}

    TokenType type;
    std::string value;
};

inline std::ostream& operator<<(std::ostream& lhs, const Token& rhs) {
    lhs << "Token(type=" << rhs.type
        << ", value=\"" << rhs.value << "\")";
    return lhs;
}
