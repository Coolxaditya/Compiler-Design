#include "Parser/Token.h"

Token::Token(TokenType type, const std::string& value, int line, int column)
    : type(type), value(value), line(line), column(column) {}