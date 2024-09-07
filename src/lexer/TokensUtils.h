#ifndef TOKEN_UTILS_H
#define TOKEN_UTILS_H

#include "Tokens.h"
#include <string>
#include <unordered_map>

namespace umbra {

const std::unordered_map<TokenType, std::string> tokenTypeToStringMap = {
    // End of file token
    {TokenType::TOK_EOF, "TOK_EOF"},
    {TokenType::TOK_NEWLINE, "TOK_NEWLINE"},

    // data types
    {TokenType::TOK_INT, "TOK_INT"},
    {TokenType::TOK_FLOAT, "TOK_FLOAT"},
    {TokenType::TOK_BOOL, "TOK_BOOL"},
    {TokenType::TOK_CHAR, "TOK_CHAR"},
    {TokenType::TOK_STRING, "TOK_STRING"},
    //{TokenType::TOK_ARRAY, "TOK_ARRAY"}, wait for array definition

    // control structures
    {TokenType::TOK_IF, "TOK_IF"},
    {TokenType::TOK_ELSE, "TOK_ELSE"},
    {TokenType::TOK_REPEAT, "TOK_REPEAT"},
    {TokenType::TOK_TIMES, "TOK_TIMES"},

    // functions and return
    {TokenType::TOK_FUNC, "TOK_FUNC"},
    {TokenType::TOK_RETURN, "TOK_RETURN"},

    // memory management
    {TokenType::TOK_NEW, "TOK_NEW"},
    {TokenType::TOK_DELETE, "TOK_DELETE"},

    // logical operators
    {TokenType::TOK_AND, "TOK_AND"}, // 'and'
    {TokenType::TOK_OR, "TOK_OR"},   // 'or'

    // comparison operators
    {TokenType::TOK_EQUAL, "TOK_EQUAL"},           // 'equal'
    {TokenType::TOK_DIFFERENT, "TOK_DIFFERENT"},   // 'different'
    {TokenType::TOK_LESS, "TOK_LESS"},             // 'less_than'
    {TokenType::TOK_GREATER, "TOK_GREATER"},       // 'greater_than'
    {TokenType::TOK_LESS_EQ, "TOK_LESS_EQ"},       // 'less_or_equal'
    {TokenType::TOK_GREATER_EQ, "TOK_GREATER_EQ"}, // 'greater_or_equal'

    // assignment token
    {TokenType::TOK_ASSIGN, "TOK_ASSIGN"}, // '='

    // arithmetic operators
    {TokenType::TOK_MINUS, "TOK_MINUS"}, // '-' (subtraction)
    {TokenType::TOK_ADD, "TOK_ADD"},     // '+' (addition)
    {TokenType::TOK_MULT, "TOK_MULT"},   // '*' (multiplication)
    {TokenType::TOK_DIV, "TOK_DIV"},     // '/' (division)

    // arrow operator (function definition)
    {TokenType::TOK_ARROW, "TOK_ARROW"}, // '->'

    // identifiers and literals
    {TokenType::TOK_IDENTIFIER, "TOK_IDENTIFIER"},
    {TokenType::TOK_NUMBER, "TOK_NUMBER"},
    {TokenType::TOK_STRING_LITERAL, "TOK_STRING_LITERAL"},

    // Symbols
    {TokenType::TOK_LEFT_BRACE, "TOK_LEFT_BRACE"},       // '{'
    {TokenType::TOK_RIGHT_BRACE, "TOK_RIGHT_BRACE"},     // '}'
    {TokenType::TOK_LEFT_BRACKET, "TOK_LEFT_BRACKET"},   // '['
    {TokenType::TOK_RIGHT_BRACKET, "TOK_RIGHT_BRACKET"}, // ']'
    {TokenType::TOK_LEFT_PAREN, "TOK_LEFT_PAREN"},
    {TokenType::TOK_RIGHT_PAREN, "TOK_RIGHT_PAREN"},
    {TokenType::TOK_COMMA, "TOK_COMMA"},
    {TokenType::TOK_DOT, "TOK_DOT"}};

// converting token to string
inline std::string tokenTypeToString(TokenType type) {
    auto it = tokenTypeToStringMap.find(type);
    if (it != tokenTypeToStringMap.end()) {
        return it->second;
    }
    return "UNKNOWN_TOKEN";
}

} // namespace umbra

#endif // TOKEN_UTILS_H
