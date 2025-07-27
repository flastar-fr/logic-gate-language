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
    PIPE,
    SEMICOLON,

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

inline std::string tostring(const TokenType& type) {
    std::string to_display;

    switch (type) {
        case TokenType::HASHTAG: {
            to_display = "HASHTAG";
            break;
        }
        case TokenType::LEFT_PAREN: {
            to_display = "LEFT_PAREN";
            break;
        }
        case TokenType::RIGHT_PAREN: {
            to_display = "RIGHT_PAREN";
            break;
        }
        case TokenType::LEFT_BRACE: {
            to_display = "LEFT_BRACE";
            break;
        }
        case TokenType::RIGHT_BRACE: {
            to_display = "RIGHT_BRACE";
            break;
        }
        case TokenType::COMMA: {
            to_display = "COMMA";
            break;
        }
        case TokenType::COLON: {
            to_display = "COLON";
            break;
        }
        case TokenType::DOT: {
            to_display = "DOT";
            break;
        }
        case TokenType::EQUAL: {
            to_display = "EQUAL";
            break;
        }
        case TokenType::PIPE: {
            to_display = "PIPE";
            break;
        }
        case TokenType::SEMICOLON: {
            to_display = "SEMICOLON";
            break;
        }
        case TokenType::RIGHT_ARROW: {
            to_display = "RIGHT_ARROW";
            break;
        }
        case TokenType::DOUBLE_SLASH: {
            to_display = "DOUBLE_SLASH";
            break;
        }
        case TokenType::IDENTIFIER: {
            to_display = "IDENTIFIER";
            break;
        }
        case TokenType::STRING: {
            to_display = "STRING";
            break;
        }
        case TokenType::BOOLEAN: {
            to_display = "BOOLEAN";
            break;
        }
        case TokenType::EOL: {
            to_display = "EOL";
            break;
        }

        default: {
            to_display = "UNKNOWN_TOKEN";
            break;
        }
    }

    return to_display;
}

inline std::ostream& operator<<(std::ostream& lhs, const TokenType& rhs) {
    lhs << tostring(rhs);
    return lhs;
}
