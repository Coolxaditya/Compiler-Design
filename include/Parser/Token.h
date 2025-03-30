#pragma once
#include <string>

enum class TokenType {
    FUNCTION_CALL,
    INCLUDE,
    KEYWORD,
    IDENTIFIER,
    STRING,
    OPERATOR,
    PUNCTUATION,
    WHITESPACE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;

    Token(TokenType type, const std::string& value, int line, int column);
};