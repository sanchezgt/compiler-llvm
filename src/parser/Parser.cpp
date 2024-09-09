#include "Parser.h"
#include "../ast/ProgramNode.h"
#include "../lexer/TokensUtils.h"
#include <iostream>
#include <stdexcept>

namespace umbra {

// Parser::Parser(Lexer &lexer) : lexer(lexer) {}

Parser::Parser(const std::vector<Lexer::Token> &tokens) : tokens(tokens), current(tokens.begin()) {}

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

/*types */
// Centralize the handling of new types
bool Parser::isTypeSpecifier(TokenType type) const {
    switch (type) {
    case TokenType::TOK_INT:
    case TokenType::TOK_FLOAT:
    case TokenType::TOK_BOOL:
    case TokenType::TOK_CHAR:
    case TokenType::TOK_STRING:
        return true;
    default:
        return false;
    }
}

TokenType Parser::parseTypeSpecifier() {
    if (isTypeSpecifier(peek().type)) {
        TokenType type = peek().type;
        advance(); // Consumir el token de tipo
        return type;
    } else {
        throw std::runtime_error("Expected type specifier, but found: " +
                                 TokenManager::tokenTypeToString(peek().type));
    }
}

/*Statements*/
std::unique_ptr<ASTNode> Parser::parseStatement() {

    // some TOK_* type
    if (isTypeSpecifier(peek().type)) {
        return parseVariableDeclaration();
    }

    switch (peek().type) {
    case TokenType::TOK_IF:
        return nullptr; // parseIfStatement();
    // Otros casos de declaraciones, como bucles, llamadas a funciones, etc.
    default:
        throw std::runtime_error("Unexpected token: " +
                                 TokenManager::tokenTypeToString(peek().type));
    }
}

std::unique_ptr<VariableDeclNode> Parser::parseVariableDeclaration() {
    TokenType type;
    type = parseTypeSpecifier();
    // TODO: Array support is needed here []
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
/*
std::unique_ptr<FunctionDeclNode> Parser::parseFunctionDefinition() {
    consume(TokenType::TOK_FUNC, "Expected 'func' at the beginning of function definition");

    // Parse the function name (identifier)
    auto token = consume(TokenType::TOK_IDENTIFIER, "Expected function name");
    std::string functionName = token.lexeme;

    // Parse the parameter list
    consume(TokenType::TOK_LEFT_PAREN, "Expected '(' after function name");
    std::vector<std::unique_ptr<ParameterNode>> parameters = parseParameterList();
    consume(TokenType::TOK_RIGHT_PAREN, "Expected ')' after parameter list");

    // Parse the return type (after '->')
    consume(TokenType::TOK_ARROW, "Expected '->' for return type");
    TokenType returnType = parseTypeSpecifier();

    // Parse the function body (statements inside braces)
    consume(TokenType::TOK_LEFT_BRACE, "Expected '{' at the beginning of function body");

    std::vector<std::unique_ptr<ASTNode>> body;
    while (!check(TokenType::TOK_RIGHT_BRACE) && !isAtEnd()) {
        body.push_back(parseStatement());
    }

    consume(TokenType::TOK_RIGHT_BRACE, "Expected '}' at the end of function body");

    // Return statement if the function is not void
    std::unique_ptr<ReturnStatementNode> returnStmt = nullptr;
    if (returnType != TokenType::TOK_VOID && match(TokenType::TOK_RETURN)) {
        returnStmt = parseReturnStatement();
    }

    return std::make_unique<FunctionDeclNode>(functionName, std::move(parameters), returnType,
                                              std::move(body), std::move(returnStmt));
}
*/
/*Expression*/

std::unique_ptr<ExpressionNode> Parser::parseExpression() {
    // TODO: Implement expression parsing
    while (!check(TokenType::TOK_NEWLINE) && !check(TokenType::TOK_EOF)) {
        advance();
    }
    return nullptr;
}

/*Utils*/

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
    if (check(type)) {
        advance();
        return currentToken;
    }
    throw std::runtime_error(message);
}

} // namespace umbra