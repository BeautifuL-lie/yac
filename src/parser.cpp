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
    std::unique_ptr<Node> root = nullptr;

    while (peek().has_value()) {
        if (get_parser_state() == EXPECT_OPERAND) {
            set_parser_state(EXPECT_OPERATOR);
            if (char op = get_last_operator(); op != '\0') {
                if (get_token_type() == TokenType::NUMBER) {
                    auto right =
                        std::make_unique<NumberNode>(get_token_value());
                    root = std::make_unique<OperatorNode>(op, std::move(root),
                                                          std::move(right));
                    set_last_operator('\0');
                    consume();
                } else if (get_token_type() == TokenType::MINUS) {
                    consume();
                    if (peek().has_value()) {
                        if (get_token_type() != TokenType::NUMBER) {
                            return nullptr;
                        }
                        int number = -get_token_value();
                        auto right = std::make_unique<NumberNode>(number);
                        root = std::make_unique<OperatorNode>(
                            op, std::move(root), std::move(right));
                        set_last_operator('\0');
                        consume();
                    }
                } else {
                    return nullptr;
                }
            } else {
                if (get_token_type() == TokenType::NUMBER) {
                    root = std::make_unique<NumberNode>(get_token_value());
                    consume();
                    set_last_operator('\0');
                } else if (get_token_type() == TokenType::MINUS) {
                    consume();
                    if (peek().has_value()) {
                        if (get_token_type() != TokenType::NUMBER) {
                            return nullptr;
                        }
                        int number = -get_token_value();
                        root = std::make_unique<NumberNode>(number);
                        consume();
                    } else {
                        return nullptr;
                    }
                } else {
                    return nullptr;
                }
            }
        } else if (get_parser_state() == EXPECT_OPERATOR) {
            set_parser_state(EXPECT_OPERAND);
            if (get_token_type() == TokenType::PLUS) {
                set_last_operator('+');
                consume();
            } else if (get_token_type() == TokenType::MINUS) {
                set_last_operator('-');
                consume();
            } else {
                return nullptr;
            }
            if (!peek().has_value()) {
                return nullptr;
            }
        } else {
            return nullptr;
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

TokenType Parser::get_token_type() {
    return m_tokens.at(m_index).m_type;
}

int Parser::get_token_value() {
    return m_tokens.at(m_index).m_value;
}

State Parser::get_parser_state() {
    return m_state;
}

void Parser::set_parser_state(State state) {
    m_state = state;
}

char Parser::get_last_operator() {
    return m_last_operator;
}

void Parser::set_last_operator(char c) {
    m_last_operator = c;
}
