#include "../include/class.hpp"
#include "../include/parser.hpp"
#include "../include/token.hpp"
#include "../include/types.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

void print_title() {
    std::cout << "~~~ Yet another calculator ~~~\n";
    std::cout << "cmd: 'quit' 'clear'\n";
}

void clear_screen() {
    std::cout << "\033[2J\033[1;1H";
}

int main() {
    print_title();
    while (true) {
        std::cout << ">> " << std::flush;

        std::string str;
        if (!std::getline(std::cin, str)) {
            break;
        }

        if (str == "quit" || str == "qui" || str == "qu" || str == "q") {
            break;
        }

        if (str == "clear" || str == "clea" || str == "cle" || str == "cl" ||
            str == "c") {
            clear_screen();
            print_title();
            continue;
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

        try {
            std::cout << "Result is " << result->evaluate() << '\n';
        } catch (const std::runtime_error &e) {
            std::cout << e.what() << '\n';
        }
    }

    return 0;
}
