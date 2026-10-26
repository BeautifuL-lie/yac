#pragma once

enum class TokenType {
    NUMBER,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    LPAR,
    RPAR
};

struct Token {
    TokenType m_type;
    int m_value = 0;
};
