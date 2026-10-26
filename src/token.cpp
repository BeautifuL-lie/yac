#include "../include/token.hpp"

#include <cctype>
#include <cstdlib>
#include <utility>

Tokenizer::Tokenizer(std::string str)
    : m_str(std::move(str)), m_len(m_str.length()), m_index(0) {}

std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens;

    while (auto current = peek()) {
        char c = current.value();

        if (std::isspace(c)) {
            consume();
        } else if (c == '+') {
            tokens.push_back({TokenType::PLUS});
            consume();
        } else if (c == '-') {
            tokens.push_back({TokenType::MINUS});
            consume();
        } else if (c == '*') {
            tokens.push_back({TokenType::STAR});
            consume();
        } else if (c == '/') {
            tokens.push_back({TokenType::SLASH});
            consume();
        } else if (c == '(') {
            tokens.push_back({TokenType::LPAR});
            consume();
        } else if (c == ')') {
            tokens.push_back({TokenType::RPAR});
            consume();
        } else if (std::isdigit(c)) {
            std::string buf;
            while (peek().has_value() && std::isdigit(peek().value())) {
                buf.push_back(consume());
            }
            int number = std::stoi(buf);
            tokens.push_back({TokenType::NUMBER, number});
        } else {
            return std::vector<Token>{};
        }
    }
    return tokens;
}

std::optional<char> Tokenizer::peek(std::size_t offset) {
    if (m_index + offset < m_len) {
        return m_str.at(m_index + offset);
    } else {
        return std::nullopt;
    }
}

char Tokenizer::consume() {
    return m_str.at(m_index++);
}
