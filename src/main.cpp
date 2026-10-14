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

    return 0;
}
