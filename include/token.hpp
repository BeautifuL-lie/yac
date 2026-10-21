#pragma once

#include "types.hpp"

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

class Tokenizer {
  public:
    Tokenizer(std::string str);

    std::vector<Token> tokenize();

  private:
    std::string m_str;
    std::size_t m_len;
    std::size_t m_index;

    std::optional<char> peek(std::size_t offset = 0);
    char consume();
};
