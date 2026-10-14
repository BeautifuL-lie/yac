#include "../include/class.hpp"
#include "../include/parser.hpp"
#include "../include/token.hpp"
#include "../include/types.hpp"

#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cout << "~~~ Yet another calculator ~~~\n";
    std::cout << "type '/exit' to quit\n";

    while (true) {
        std::cout << "> ";

        std::string str;
        if (!std::getline(std::cin, str)) {
            break;
        }

        if (str == "/exit") {
            break;
        }

        std::vector<Token> tokens = tokenize(str);
        if (tokens.empty()) {
            std::cout << "Invalid expression!\n";
            continue;
        }

        auto result = parser(tokens);
        if (result == nullptr) {
            std::cout << "Invalid expression!\n";
            continue;
        }

        std::cout << "Result is " << result->evaluate() << '\n';
    }

    return 0;
}
