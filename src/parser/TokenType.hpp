#pragma once

enum class TokenType {
    // symbols single char
    HASHTAG,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    COLON,
    DOT,
    EQUAL,

    // symbols two chars
    RIGHT_ARROW,
    DOUBLE_SLASH,

    // literals
    IDENTIFIER,
    STRING,
    BOOLEAN,

    // special
    EOL
};
