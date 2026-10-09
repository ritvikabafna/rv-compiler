#include "Lexer.hpp"

#include <cassert>
#include <iostream>

int main() {

    rv::Lexer lexer(
        "fn main() {\n"
        "  let score = 25;\n"
        "  if (score >= 20 && true) {\n"
        "    return \"Passed\"; // done\n"
        "  }\n"
        "}"
    );

    auto tokens = lexer.tokenize();

    // Total tokens:
    // 23 actual tokens + EOF = 25
    assert(tokens.size() == 25);

    // 0: fn
    assert(tokens[0].kind == rv::TokenKind::Fn);
    assert(tokens[0].lexeme == "fn");
    assert(tokens[0].line == 1);
    assert(tokens[0].column == 1);

    // 1: main
    assert(tokens[1].kind == rv::TokenKind::Identifier);
    assert(tokens[1].lexeme == "main");
    assert(tokens[1].line == 1);
    assert(tokens[1].column == 4);

    // 2: (
    assert(tokens[2].kind == rv::TokenKind::LParen);
    assert(tokens[2].lexeme == "(");
    assert(tokens[2].line == 1);
    assert(tokens[2].column == 8);

    // 3: )
    assert(tokens[3].kind == rv::TokenKind::RParen);
    assert(tokens[3].lexeme == ")");
    assert(tokens[3].line == 1);
    assert(tokens[3].column == 9);

    // 4: {
    assert(tokens[4].kind == rv::TokenKind::LBrace);
    assert(tokens[4].lexeme == "{");
    assert(tokens[4].line == 1);
    assert(tokens[4].column == 11);

    // 5: let
    assert(tokens[5].kind == rv::TokenKind::Let);
    assert(tokens[5].lexeme == "let");
    assert(tokens[5].line == 2);
    assert(tokens[5].column == 3);

    // 6: score
    assert(tokens[6].kind == rv::TokenKind::Identifier);
    assert(tokens[6].lexeme == "score");
    assert(tokens[6].line == 2);
    assert(tokens[6].column == 7);

    // 7: =
    assert(tokens[7].kind == rv::TokenKind::Equal);
    assert(tokens[7].lexeme == "=");
    assert(tokens[7].line == 2);
    assert(tokens[7].column == 13);

    // 8: 25
    assert(tokens[8].kind == rv::TokenKind::IntegerLiteral);
    assert(tokens[8].lexeme == "25");
    assert(tokens[8].line == 2);
    assert(tokens[8].column == 15);

    // 9: ;
    assert(tokens[9].kind == rv::TokenKind::Semicolon);
    assert(tokens[9].lexeme == ";");
    assert(tokens[9].line == 2);
    assert(tokens[9].column == 17);

    // 10: if
    assert(tokens[10].kind == rv::TokenKind::If);
    assert(tokens[10].lexeme == "if");
    assert(tokens[10].line == 3);
    assert(tokens[10].column == 3);

    // 11: (
    assert(tokens[11].kind == rv::TokenKind::LParen);
    assert(tokens[11].lexeme == "(");
    assert(tokens[11].line == 3);
    assert(tokens[11].column == 6);

    // 12: score
    assert(tokens[12].kind == rv::TokenKind::Identifier);
    assert(tokens[12].lexeme == "score");
    assert(tokens[12].line == 3);
    assert(tokens[12].column == 7);

    // 13: >=
    assert(tokens[13].kind == rv::TokenKind::GreaterEqual);
    assert(tokens[13].lexeme == ">=");
    assert(tokens[13].line == 3);
    assert(tokens[13].column == 13);

    // 14: 20
    assert(tokens[14].kind == rv::TokenKind::IntegerLiteral);
    assert(tokens[14].lexeme == "20");
    assert(tokens[14].line == 3);
    assert(tokens[14].column == 16);

    // 15: &&
    assert(tokens[15].kind == rv::TokenKind::AndAnd);
    assert(tokens[15].lexeme == "&&");
    assert(tokens[15].line == 3);
    assert(tokens[15].column == 19);

    // 16: true
    assert(tokens[16].kind == rv::TokenKind::True);
    assert(tokens[16].lexeme == "true");
    assert(tokens[16].line == 3);
    assert(tokens[16].column == 22);

    // 17: )
    assert(tokens[17].kind == rv::TokenKind::RParen);
    assert(tokens[17].lexeme == ")");
    assert(tokens[17].line == 3);
    assert(tokens[17].column == 26);

    // 18: {
    assert(tokens[18].kind == rv::TokenKind::LBrace);
    assert(tokens[18].lexeme == "{");
    assert(tokens[18].line == 3);
    assert(tokens[18].column == 28);

    // 19: return
    assert(tokens[19].kind == rv::TokenKind::Return);
    assert(tokens[19].lexeme == "return");
    assert(tokens[19].line == 4);
    assert(tokens[19].column == 5);

    // 20: "Passed"
    assert(tokens[20].kind == rv::TokenKind::StringLiteral);
    assert(tokens[20].lexeme == "\"Passed\"");
    assert(tokens[20].line == 4);
    assert(tokens[20].column == 12);

    // 21: ;
    assert(tokens[21].kind == rv::TokenKind::Semicolon);
    assert(tokens[21].lexeme == ";");
    assert(tokens[21].line == 4);
    assert(tokens[21].column == 20);

    // 22: }
    assert(tokens[22].kind == rv::TokenKind::RBrace);
    assert(tokens[22].lexeme == "}");
    assert(tokens[22].line == 5);
    assert(tokens[22].column == 3);

    // 23: }
    assert(tokens[23].kind == rv::TokenKind::RBrace);
    assert(tokens[23].lexeme == "}");
    assert(tokens[23].line == 6);
    assert(tokens[23].column == 1);

    // 24: EOF
    assert(tokens[24].kind == rv::TokenKind::Eof);
    assert(tokens[24].lexeme == "");
    assert(tokens[24].line == 6);
    assert(tokens[24].column == 2);

    std::cout << "Lexer integration test passed!\n";

    return 0;
}