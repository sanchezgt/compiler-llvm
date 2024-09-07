#include "Parser.h"
#include "../lexer/TokensUtils.h"
#include <iostream>
#include <stdexcept>
namespace umbra {

// Parser::Parser(Lexer &lexer) : lexer(lexer) {}

Parser::Parser(const std::vector<Lexer::Token> &tokens) : tokens(tokens) {}

std::unique_ptr<ASTNode> Parser::parse() {
    std::vector<std::unique_ptr<ASTNode>> ast;

    while (!isAtEnd()) {
        try {
            ast.push_back(parseStatement());
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            // Skip to the next newline or EOF
            while (!isAtEnd() && !match(TokenType::TOK_NEWLINE)) {
                advance();
            }
        }
    }

    return std::make_unique<ProgramNode>(std::move(ast));
}

std::unique_ptr<ASTNode> Parser::parseStatement() {
    if (check(TokenType::TOK_INT) || check(TokenType::TOK_FLOAT) || 
        check(TokenType::TOK_BOOL) || check(TokenType::TOK_CHAR) || 
        check(TokenType::TOK_STRING)) {
        return parseVariableDeclaration();
    }
    // Add more statement types here as you implement them
    // For example:
    // if (match(TokenType::TOK_IF)) {
    //     return parseIfStatement();
    // }
    
    throw std::runtime_error("Unexpected token: " + tokenTypeToString(peek().type));
}

std::unique_ptr<VariableDeclNode> Parser::parseVariableDeclaration() {
    TokenType type;
    if (match(TokenType::TOK_INT))
        type = TokenType::TOK_INT;
    else if (match(TokenType::TOK_FLOAT))
        type = TokenType::TOK_FLOAT;
    else if (match(TokenType::TOK_BOOL))
        type = TokenType::TOK_BOOL;
    else if (match(TokenType::TOK_CHAR))
        type = TokenType::TOK_CHAR;
    else if (match(TokenType::TOK_STRING))
        type = TokenType::TOK_STRING;
    else {
        // token que causó el fallo
        std::string errorMsg =
            "Expected type specifier, but found: " + tokenTypeToString(peek().type);
        throw std::runtime_error(errorMsg);
    }

    // TODO: Handle array size if present
    // if (match(TokenType::TOK_LEFT_BRACKET)) {
    //     // Parse array size
    //     consume(TokenType::TOK_RIGHT_BRACKET, "Expected ']' after array size");
    // }
    auto token = consume(TokenType::TOK_IDENTIFIER, "Expected variable name");
    std::string name = token.lexeme;

    std::unique_ptr<ExpressionNode> initializer = nullptr;
    if (match(TokenType::TOK_ASSIGN)) {
        initializer = parseExpression();
    }

    if (!match(TokenType::TOK_NEWLINE)) {
        throw std::runtime_error("Expected newline after variable declaration");
    }

    return std::make_unique<VariableDeclNode>(type, name, std::move(initializer));
}

std::unique_ptr<ExpressionNode> Parser::parseExpression() {
    // TODO: Implement expression parsing
    // For now, we'll just consume tokens until we hit a newline or semicolon
    while (!check(TokenType::TOK_NEWLINE) && !check(TokenType::TOK_EOF)) {
        advance();
    }
    return nullptr;
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) const {
    if (isAtEnd())
        return false;
    return peek().type == type;
}

Lexer::Token Parser::advance() {
    if (!isAtEnd())
        current++;
    return peek();
}

Lexer::Token Parser::peek() const { return *current; }

bool Parser::isAtEnd() const { return peek().type == TokenType::TOK_EOF; }

Lexer::Token Parser::consume(TokenType type, const std::string &message) {
    Lexer::Token currentToken = peek();
    if (check(type))
        advance();
    return currentToken;
    throw std::runtime_error(message);
}

} // namespace umbra