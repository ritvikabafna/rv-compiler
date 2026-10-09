#include "Lexer.hpp"

#include <cassert>
#include <iostream>

int main() {
    const std::string source = R"(
fn calculate {
    let x = 25;
    let y = 3.14;

    if x >= 10 && y != 0 {
        return x + y * 2;
    }

    return 0;
}
)";

    rv::Lexer lexer(source);

    const auto tokens = lexer.tokenize();

    for (const auto& token : tokens) {
        std::cout
            << "Line " << token.line
            << ", Column " << token.column
            << " -> "
            << token.lexeme
            << '\n';
    }

    return 0;
}