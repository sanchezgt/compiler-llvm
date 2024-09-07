// Tokens.h
#ifndef TOKENS_H
#define TOKENS_H

namespace umbra {

enum class TokenType {
    // End of file token
    TOK_EOF,
    TOK_NEWLINE,

    // Keyword tokens for data types
    TOK_INT,
    TOK_FLOAT,
    TOK_BOOL,
    TOK_CHAR,
    TOK_STRING,
    // TOK_ARRAY, wait for array definition

    // Keyword tokens for control structures
    TOK_IF,
    TOK_ELSE,
    TOK_REPEAT,
    TOK_TIMES,

    // Keyword tokens for functions and return
    TOK_FUNC,
    TOK_RETURN,

    // Tokens for memory management
    TOK_NEW,
    TOK_DELETE,

    // Tokens for logical operators
    TOK_AND, // 'and'
    TOK_OR,  // 'or'

    // Tokens for comparison operators
    TOK_EQUAL,      // 'equal'
    TOK_DIFFERENT,  // 'different'
    TOK_LESS,       // 'less_than'
    TOK_GREATER,    // 'greater_than'
    TOK_LESS_EQ,    // 'less_or_equal'
    TOK_GREATER_EQ, // 'greater_or_equal'

    // Assignment token
    TOK_ASSIGN, // '='

    // Tokens for arithmetic operators
    TOK_MINUS, // '-' (subtraction)
    TOK_ADD,   // '+' (addition)
    TOK_MULT,  // '*' (multiplication)
    TOK_DIV,   // '/' (division)

    // Token for arrow operator (function definition)
    TOK_ARROW, // '->'

    // Tokens for identifiers and literals
    TOK_IDENTIFIER,
    TOK_NUMBER,
    TOK_STRING_LITERAL,

    // Symbols
    TOK_LEFT_BRACE,  // '{'
    TOK_RIGHT_BRACE, // '}'
    TOK_LEFT_BRACKET,
    TOK_RIGHT_BRACKET,
    TOK_LEFT_PAREN,
    TOK_RIGHT_PAREN,
    TOK_COMMA,
    TOK_DOT

};

} // namespace umbra

#endif // TOKENS_H
