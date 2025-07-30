#pragma once
#include <string>
#include <utility>
#include <ostream>

#include "TokenType.hpp"

struct Token {
    explicit Token(const TokenType type) : type(type) {}
    explicit Token(const TokenType type, std::string value) : type(type), value(std::move(value)) {}
    explicit Token(const TokenType type, const size_t line) : type(type), line(line) {}
    explicit Token(const TokenType type, std::string value, const size_t line) : type(type), value(std::move(value)), line(line) {}

    TokenType type;
    std::string value;
    size_t line = 1;
};

inline std::ostream& operator<<(std::ostream& lhs, const Token& rhs) {
    lhs << "Token(type=" << rhs.type
        << ", value=\"" << rhs.value << "\")";
    return lhs;
}

inline bool operator==(const Token& lhs, const Token& rhs) {
    return lhs.type == rhs.type && lhs.value == rhs.value;
}
