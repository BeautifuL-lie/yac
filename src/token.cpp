#include "../include/token.hpp"

#include "../include/types.hpp"

#include <iostream>
#include <sstream>
#include <vector>

std::vector<Token> tokenize(const std::string &str) {
    std::vector<Token> tokens;
    const std::size_t len = str.size();
    for (std::size_t i = 0; i < len; i++) {
        if (std::isspace(str[i])) {
            continue;
        } else if (str[i] == '+') {
            tokens.push_back({TokenType::PLUS});
        } else if (str[i] == '-') {
            tokens.push_back({TokenType::MINUS});
        } else if (std::isdigit(str[i])) {
            std::string tmp;
            while (i < len && std::isdigit(str[i])) {
                tmp.push_back(str[i]);
                i++;
            }
            i--;

            int number;
            std::istringstream ss(tmp);
            ss >> number;

            tokens.push_back({TokenType::NUMBER, number});
        } else {
            return std::vector<Token>{};
        }
    }
    return tokens;
}

std::string get_token_type(TokenType type) {
    switch (type) {
    case TokenType::NUMBER:
        return "NUMBER";
    case TokenType::PLUS:
        return "PLUS";
    case TokenType::MINUS:
        return "MINUS";
    }
    return "UNKNOWN";
}
