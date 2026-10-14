#include "../include/parser.hpp"

#include "../include/class.hpp"
#include "../include/types.hpp"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

void parser(const std::vector<Token> &tokens) {
    std::unique_ptr<Node> root = nullptr;

    const std::size_t len = tokens.size();
    for (std::size_t i = 0; i < len; i++) {
        if (tokens[i].m_type == TokenType::NUMBER) {
            if (!root) {
                root = std::make_unique<NumberNode>(tokens[i].m_value);
            }
        } else {
            if (i == 0) {
                std::cout << "Invalid expression!\n";
                std::exit(1);
            }

            i++;
            if (i >= len) {
                std::cout << "Invalid expression!\n";
                std::exit(1);
            }

            if (tokens[i - 1].m_type == TokenType::PLUS) {
                root = std::make_unique<OperatorNode>(
                    '+', std::move(root),
                    std::make_unique<NumberNode>(tokens[i].m_value));
            } else {
                root = std::make_unique<OperatorNode>(
                    '-', std::move(root),
                    std::make_unique<NumberNode>(tokens[i].m_value));
            }
        }
    }

    std::cout << "Result is " << root->evaluate() << '\n';
}
