#include "../include/parser.hpp"
#include "../include/token.hpp"
#include "../include/types.hpp"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

int main() {
    const std::string str = "10-5+1-  2";
    std::vector<Token> tokens = tokenize(str);
    const std::size_t len = tokens.size();

    parser(tokens);

    // for (std::size_t i = 0; i < len; i++) {
    //     if (tokens[i].m_type == TokenType::NUMBER) {
    //         std::cout << "NUMBER(" << tokens[i].m_value << ")" << '\n';
    //     } else {
    //         std::cout << get_token_type(tokens[i].m_type) << '\n';
    //     }
    // }

    return 0;
}
