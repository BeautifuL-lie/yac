#include "../include/parser.hpp"

#include "../include/class.hpp"
#include "../include/types.hpp"

#include <cstddef>
#include <cstdlib>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

Parser::Parser(std::vector<Token> tokens)
    : m_tokens(tokens), m_len(m_tokens.size()) {}

std::unique_ptr<Node> Parser::parse() {
    auto root = parse_expression();

    if (peek().has_value()) {
        return nullptr;
    }

    return root;
}

std::unique_ptr<Node> Parser::parse_expression() {
    auto left = parse_term();
    if (!left) {
        return nullptr;
    }

    while (peek().has_value()) {
        const TokenType type = get_token_type();
        if (type == TokenType::PLUS || type == TokenType::MINUS) {
            char op = (type == TokenType::PLUS) ? '+' : '-';
            consume();

            auto right = parse_term();
            if (!right) {
                return nullptr;
            }

            left = std::make_unique<OperatorNode>(op, std::move(left),
                                                  std::move(right));
        } else {
            break;
        }
    }

    return left;
}

std::unique_ptr<Node> Parser::parse_term() {
    auto left = parse_factor();
    if (!left) {
        return nullptr;
    }

    while (peek().has_value()) {
        const TokenType type = get_token_type();
        if (type == TokenType::STAR || type == TokenType::SLASH) {
            char op = (type == TokenType::STAR) ? '*' : '/';
            consume();

            auto right = parse_factor();
            if (!right) {
                return nullptr;
            }

            left = std::make_unique<OperatorNode>(op, std::move(left),
                                                  std::move(right));
        } else {
            break;
        }
    }

    return left;
}

std::unique_ptr<Node> Parser::parse_factor() {
    if (!peek().has_value()) {
        return nullptr;
    }

    const TokenType type = get_token_type();
    if (type == TokenType::NUMBER) {
        int value = get_token_value();
        consume();
        return std::make_unique<NumberNode>(value);
    } else if (type == TokenType::MINUS) {
        consume();
        if (!peek().has_value() || get_token_type() != TokenType::NUMBER) {
            return nullptr;
        }
        int value = -get_token_value();
        consume();
        return std::make_unique<NumberNode>(value);
    } else if (type == TokenType::LPAR) {
        consume();

        auto node = parse_expression();
        if (!node) {
            return nullptr;
        }

        if (!peek().has_value() || get_token_type() != TokenType::RPAR) {
            return nullptr;
        }
        consume();
        return node;
    }

    return nullptr;
}

std::optional<Token> Parser::peek(std::size_t offset) {
    if (m_index + offset < m_len) {
        return m_tokens.at(m_index + offset);
    } else {
        return std::nullopt;
    }
}

Token Parser::consume() {
    return m_tokens.at(m_index++);
}

TokenType Parser::get_token_type() {
    return m_tokens.at(m_index).m_type;
}

int Parser::get_token_value() {
    return m_tokens.at(m_index).m_value;
}
