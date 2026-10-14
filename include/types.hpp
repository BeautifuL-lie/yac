#pragma once

enum class TokenType {
    NUMBER,
    PLUS,
    MINUS
};

struct Token {
    TokenType m_type;
    int m_value = 0;
};
