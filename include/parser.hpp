#pragma once

#include "class.hpp"
#include "types.hpp"

#include <memory>
#include <optional>
#include <vector>

class Parser {
  public:
    Parser(std::vector<Token> tokens);

    std::unique_ptr<Node> parse();

  private:
    std::vector<Token> m_tokens;
    std::size_t m_len;
    std::size_t m_index = 0;

    std::optional<Token> peek(std::size_t offset = 0);
    Token consume();
    TokenType get_token_type();
    int get_token_value();
    std::unique_ptr<Node> parse_factor();
    std::unique_ptr<Node> parse_expression();
    std::unique_ptr<Node> parse_term();
};
