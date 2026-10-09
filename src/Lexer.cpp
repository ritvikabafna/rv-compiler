#include "Lexer.hpp"
#include "LexerError.hpp"
#include <utility>


namespace rv {

Lexer::Lexer(std::string source)
    : source_(std::move(source)) {
}

//helper function

char Lexer::advance() {
    char character = source_[current_];
    ++current_;

    if (character == '\n') {
        ++line_;
        column_ = 1;
    } else {
        ++column_;
    }

    return character;
}

bool Lexer::isAtEnd() const {
    return current_ >= source_.size();
}

char Lexer::peek() const {
    if (isAtEnd()) {
        return '\0';
    }

    return source_[current_];
}

char Lexer::peekNext() const {
    if (current_ + 1 >= source_.size()) {
        return '\0';
    }

    return source_[current_ + 1];
}

bool Lexer::match(char expected) {
    if (isAtEnd()) {
        return false;
    }

    if (source_[current_] != expected) {
        return false;
    }

    advance();
    return true;
}
//------------------------------------------------------------
// token scanning function

Token Lexer::scanIdentifier() {
    const std::size_t start = current_;
    const std::size_t startColumn = column_;

    while (true) {
        const char c = peek();

        if ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') ||
            c == '_') {
            advance();
        } else {
            break;
        }
    }

    const std::string lexeme =
        source_.substr(start, current_ - start);

    TokenKind kind = TokenKind::Identifier;

    if (lexeme == "fn") {
        kind = TokenKind::Fn;
    } else if (lexeme == "let") {
        kind = TokenKind::Let;
    } else if (lexeme == "if") {
        kind = TokenKind::If;
    } else if (lexeme == "else") {
        kind = TokenKind::Else;
    } else if (lexeme == "while") {
        kind = TokenKind::While;
    } else if (lexeme == "return") {
        kind = TokenKind::Return;
    } else if (lexeme == "true") {
        kind = TokenKind::True;
    } else if (lexeme == "false") {
        kind = TokenKind::False;
    }

    return Token{
        kind,
        lexeme,
        line_,
        startColumn
    };
}

//-----------------------SCAN NUMBER----------------------------------------

Token Lexer::scanNumber() {
    const std::size_t start = current_;
    const std::size_t startColumn = column_;
    const std::size_t startLine = line_;

    // Consume the integer part.
    while (peek() >= '0' && peek() <= '9') {
        advance();
    }

    if ((peek() >= 'a' && peek() <= 'z') ||
    (peek() >= 'A' && peek() <= 'Z') ||
    peek() == '_') {
    throw LexerError(
        "invalid numeric literal",
        startLine,
        startColumn
    );
}

    bool isFloat = false;

    // Check for a decimal point followed by a digit.
    if (peek() == '.' &&
        peekNext() >= '0' &&
        peekNext() <= '9') {
        isFloat = true;
        advance(); // Consume '.'

        while (peek() >= '0' && peek() <= '9') {
            advance();
        }
    }

    if (peek() == '.') {
    throw LexerError(
        "invalid numeric literal",
        startLine,
        startColumn
    );
}

    const std::string lexeme =
        source_.substr(start, current_ - start);

    return Token{
        isFloat ? TokenKind::FloatLiteral
                : TokenKind::IntegerLiteral,
        lexeme,
        startLine,
        startColumn
    };
}

//--------------SCAN OPERATOR---------------------

Token Lexer::scanOperator() {
    const std::size_t start = current_;
    const std::size_t startLine = line_;
    const std::size_t startColumn = column_;

    const char c = advance();

    switch (c) {
        case '+':
            return makeToken(
                TokenKind::Plus,
                start,
                startLine,
                startColumn
            );

        case '-':
            return makeToken(
                TokenKind::Minus,
                start,
                startLine,
                startColumn
            );

        case '*':

            return makeToken(
                TokenKind::Star,
                start,
                startLine,
                startColumn
            );

        case '/':


            return makeToken(
                TokenKind::Slash,
                start,
                startLine,
                startColumn
            );

        case '%':
            return makeToken(
                TokenKind::Percent,
                start,
                startLine,
                startColumn
            );

        case '=':
            if (match('=')) {
                return makeToken(
                    TokenKind::EqualEqual,
                    start,
                    startLine,
                    startColumn
                );
            }

            return makeToken(
                TokenKind::Equal,
                start,
                startLine,
                startColumn
            );

        case '!':
            if (match('=')) {
                return makeToken(
                    TokenKind::BangEqual,
                    start,
                    startLine,
                    startColumn
                );
            }

            return makeToken(
                TokenKind::Bang,
                start,
                startLine,
                startColumn
            );

        case '<':
            if (match('=')) {
                return makeToken(
                    TokenKind::LessEqual,
                    start,
                    startLine,
                    startColumn
                );
            }

            return makeToken(
                TokenKind::Less,
                start,
                startLine,
                startColumn
            );

        case '>':
            if (match('=')) {
                return makeToken(
                    TokenKind::GreaterEqual,
                    start,
                    startLine,
                    startColumn
                );
            }

            return makeToken(
                TokenKind::Greater,
                start,
                startLine,
                startColumn
            );

        case '&':
            if (match('&')) {
                return makeToken(
                    TokenKind::AndAnd,
                    start,
                    startLine,
                    startColumn
                );
            }

            throw LexerError(
                "expected '&' after '&'",
                startLine,
                startColumn
            );

        case '|':
            if (match('|')) {
                return makeToken(
                    TokenKind::OrOr,
                    start,
                    startLine,
                    startColumn
                );
            }

            throw LexerError(
                "expected '|' after '|'",
                startLine,
                startColumn
            );

        default:
            throw LexerError(
                "unknown operator",
                startLine,
                startColumn
            );
    }
}

// --------------Scan Delimeter------------------------------

Token Lexer::scanDelimiter() {
    const std::size_t start = current_;
    const std::size_t startLine = line_;
    const std::size_t startColumn = column_;

    const char c = advance();

    switch (c) {
        case '(':
            return makeToken(
                TokenKind::LParen,
                start,
                startLine,
                startColumn
            );

        case ')':
            return makeToken(
                TokenKind::RParen,
                start,
                startLine,
                startColumn
            );

        case '{':
            return makeToken(
                TokenKind::LBrace,
                start,
                startLine,
                startColumn
            );

        case '}':
            return makeToken(
                TokenKind::RBrace,
                start,
                startLine,
                startColumn
            );

        case '[':
            return makeToken(
                TokenKind::LBracket,
                start,
                startLine,
                startColumn
            );

        case ']':
            return makeToken(
                TokenKind::RBracket,
                start,
                startLine,
                startColumn
            );

        case ',':
            return makeToken(
                TokenKind::Comma,
                start,
                startLine,
                startColumn
            );

        case ';':
            return makeToken(
                TokenKind::Semicolon,
                start,
                startLine,
                startColumn
            );

        case ':':
            return makeToken(
                TokenKind::Colon,
                start,
                startLine,
                startColumn
            );
    }

    throw LexerError(
        "invalid delimiter",
        startLine,
        startColumn
    );
}

// ------------------skip Comments -------------------

void Lexer::skipComment() {
    // Consume everything until newline or end of source.
    while (!isAtEnd() && peek() != '\n') {
        advance();
    }
}

//-------------Scan String--------------

Token Lexer::scanString() {
    const std::size_t start = current_;
    const std::size_t startLine = line_;
    const std::size_t startColumn = column_;

    advance(); // Consume opening quote.

    while (!isAtEnd() && peek() != '"') {
        if (peek() == '\n' || peek() == '\r') {
            throw LexerError(
                "unterminated string",
                startLine,
                startColumn
            );
        }

        if (peek() == '\\') {
            advance(); // Consume backslash.

            if (isAtEnd()) {
                throw LexerError(
                    "unterminated string",
                    startLine,
                    startColumn
                );
            }

            const char escaped = advance();

            if (escaped != 'n' &&
                escaped != 't' &&
                escaped != 'r' &&
                escaped != '\\' &&
                escaped != '"') {
                throw LexerError(
                    "invalid escape sequence",
                    line_,
                    column_ - 1
                );
            }
        } else {
            advance();
        }
    }

    if (isAtEnd()) {
        throw LexerError(
            "unterminated string",
            startLine,
            startColumn
        );
    }

    advance(); // Consume closing quote.

    return makeToken(
        TokenKind::StringLiteral,
        start,
        startLine,
        startColumn
    );
}

//----------Make Token-----------------------------

Token Lexer::makeToken(
    TokenKind kind,
    std::size_t start,
    std::size_t startLine,
    std::size_t startColumn
) {
    return Token{
        kind,
        source_.substr(start, current_ - start),
        startLine,
        startColumn
    };
}

//--------------Tokenize--------------------

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (!isAtEnd()) {
        const char c = peek();

        // Skip whitespace.
        if (c == ' ' || c == '\t'  || c == '\r' || c == '\n') {
            advance();
            continue;
        }

        // Identifier or keyword.
        if ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            c == '_') {
            tokens.push_back(scanIdentifier());
            continue;
        }

        //------------number---------------------
        if (c >= '0' && c <= '9') {
        tokens.push_back(scanNumber());
        continue;
        }

        //--------comments -----------
        if (c == '/' && peekNext() == '/') {
            advance();
            advance();
            skipComment();
            continue;
        }

        //---------------Scan Delimeter--------------------

        if (c == '+' ||
            c == '-' ||
            c == '*' ||
            c == '/' ||
            c == '%' ||
            c == '=' ||
            c == '!' ||
            c == '<' ||
            c == '>' ||
            c == '&' ||
            c == '|') {
            tokens.push_back(scanOperator());
            continue;
        }
        //---------------delimeter--------------------

        if (c == '(' ||
            c == ')' ||
            c == '{' ||
            c == '}' ||
            c == '[' ||
            c == ']' ||
            c == ',' ||
            c == ';' ||
            c == ':') {
            tokens.push_back(scanDelimiter());
            continue;
        }

        //-----------scan string-------------
        if (c == '"') {
            tokens.push_back(scanString());
            continue;
        }       
        // Unknown character for now.
        throw LexerError(
            "unknown character",
            line_,
            column_
        );
    }

    tokens.push_back(Token{
        TokenKind::Eof,
        "",
        line_,
        column_
    });

    return tokens;
}

} // namespace rv

