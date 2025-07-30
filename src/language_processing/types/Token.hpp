#pragma once
#include <string>
#include <utility>
#include <ostream>

#include "TokenType.hpp"

struct Token {
    explicit Token(const TokenType type) : type(type) {}
    explicit Token(const TokenType type, std::string value) : type(type), value(std::move(value)) {}

    TokenType type;
    std::string value;
};

inline std::ostream& operator<<(std::ostream& lhs, const Token& rhs) {
    lhs << "Token(type=" << rhs.type
        << ", value=\"" << rhs.value << "\")";
    return lhs;
}

inline bool operator==(const Token& lhs, const Token& rhs) {
    return lhs.type == rhs.type && lhs.value == rhs.value;
}
