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
    : m_tokens(tokens), m_len(m_tokens.size()), m_index(0) {}

std::unique_ptr<Node> Parser::parse() {

    std::unique_ptr<Node> root = nullptr;

    const std::size_t len = m_tokens.size();
    for (std::size_t i = 0; i < len; i++) {
        if (m_tokens[i].m_type == TokenType::NUMBER) {
            if (!root) {
                root = std::make_unique<NumberNode>(m_tokens[i].m_value);
            }
        } else {
            if (i == 0) {
                return nullptr;
            }

            i++;
            if (i >= len) {
                return nullptr;
            }

            if (m_tokens[i].m_type == TokenType::PLUS ||
                m_tokens[i].m_type == TokenType::MINUS) {
                return nullptr;
            }

            if (m_tokens[i - 1].m_type == TokenType::PLUS) {
                root = std::make_unique<OperatorNode>(
                    '+', std::move(root),
                    std::make_unique<NumberNode>(m_tokens[i].m_value));
            } else {
                root = std::make_unique<OperatorNode>(
                    '-', std::move(root),
                    std::make_unique<NumberNode>(m_tokens[i].m_value));
            }
        }
    }
    return root;
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
