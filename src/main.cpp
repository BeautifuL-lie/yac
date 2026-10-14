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
        parser(tokens);
    }

    return 0;
}
