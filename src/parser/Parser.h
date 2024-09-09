#ifndef PARSER_H
#define PARSER_H

#include "../ast/ASTNode.h"
#include "../ast/statementnodes/StatementNode.h"
#include "../lexer/Lexer.h"
#include <memory>
#include <vector>

namespace umbra {

class Parser {
  public:
    // Parser(Lexer &lexer);
    Parser(const std::vector<Lexer::Token> &tokens);

    std::unique_ptr<ASTNode> parse();

  private:
    // Lexer &lexer;
    std::vector<Lexer::Token> tokens;
    std::vector<Lexer::Token>::const_iterator current;

    std::unique_ptr<ASTNode> parseStatement();
    std::unique_ptr<VariableDeclNode> parseVariableDeclaration();
    std::unique_ptr<FunctionDeclNode> parseFunctionDefinition();
    std::unique_ptr<ExpressionNode> parseExpression();
    TokenType parseTypeSpecifier();
    bool isTypeSpecifier(TokenType type) const;

    bool match(TokenType type);
    bool check(TokenType type) const;
    Lexer::Token advance();
    Lexer::Token peek() const;
    bool isAtEnd() const;
    Lexer::Token consume(TokenType type, const std::string &message);
};

} // namespace umbra

#endif // PARSER_H