#pragma once

#include "class.hpp"
#include "types.hpp"

#include <vector>

std::unique_ptr<Node> parser(const std::vector<Token> &tokens);
