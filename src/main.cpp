#include "../include/class.hpp"
#include "../include/parser.hpp"
#include "../include/token.hpp"
#include "../include/types.hpp"

#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cout << "~~~ Yet another calculator ~~~\n";
    std::cout << "type 'quit' to exit\n";

    while (true) {
        std::cout << ">> " << std::flush;

        std::string str;
        if (!std::getline(std::cin, str)) {
            break;
        }

        if (str == "quit" || str == "qui" || str == "qu" || str == "q") {
            break;
        }

        Tokenizer tokenizer(str);
        std::vector<Token> tokens = tokenizer.tokenize();

        if (tokens.empty()) {
            std::cout << "Invalid expression!\n";
            continue;
        }

        Parser parser(tokens);
        auto result = parser.parse();
        if (result == nullptr) {
            std::cout << "Invalid expression!\n";
            continue;
        }

        std::cout << "Result is " << result->evaluate() << '\n';
    }

    return 0;
}
