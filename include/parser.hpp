#pragma once

#include "class.hpp"
#include "types.hpp"

#include <memory>
#include <optional>
#include <vector>

enum State {
    EXPECT_OPERAND,
    EXPECT_OPERATOR
};

class Parser {
  public:
    Parser(std::vector<Token> tokens);

    std::unique_ptr<Node> parse();

  private:
    std::vector<Token> m_tokens;
    std::size_t m_len;
    std::size_t m_index = 0;
    State m_state = EXPECT_OPERAND;
    char m_last_operator = '\0';

    std::optional<Token> peek(std::size_t offset = 0);
    Token consume();
    TokenType get_token_type();
    int get_token_value();
    State get_parser_state();
    void set_parser_state(State);
    char get_last_operator();
    void set_last_operator(char c);
};
