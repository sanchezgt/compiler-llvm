#ifndef STATEMENTNODE_H
#define STATEMENTNODE_H

#include "../../lexer/Tokens.h"
#include "../ASTNode.h"
#include "../expressionnodes/ExpressionNode.h"
#include <iostream>
#include <memory>
#include <vector>

namespace umbra {

class StatementNode : public ASTNode {
  public:
    virtual ~StatementNode() noexcept = default;
};

class VariableDeclNode : public StatementNode {
  public:
    VariableDeclNode(TokenType type, const std::string &name,
                     std::unique_ptr<ExpressionNode> initializer = nullptr);

    TokenType getType() const { return type; }
    const std::string &getName() const { return name; }
    const ExpressionNode *getInitializer() const { return initializer.get(); }

    void accept(ASTVisitor &visitor) override;
    ~VariableDeclNode() noexcept override = default;

  private:
    TokenType type;
    std::string name;
    std::unique_ptr<ExpressionNode> initializer;
};

class ParameterNode : public ASTNode {
  public:
    ParameterNode(TokenType type, const std::string &name) : type(type), name(name) {}

    TokenType getType() const { return type; }
    const std::string &getName() const { return name; }

  private:
    TokenType type;
    std::string name;
};

class ReturnStatementNode : public StatementNode {
  public:
    ReturnStatementNode(std::unique_ptr<ExpressionNode> returnValue)
        : returnValue(std::move(returnValue)) {}

    const ExpressionNode *getReturnValue() const { return returnValue.get(); }

    ~ReturnStatementNode() noexcept override = default;

  private:
    std::unique_ptr<ExpressionNode> returnValue;
};

class FunctionDeclNode : public StatementNode {
  public:
    FunctionDeclNode(std::string name, std::vector<std::unique_ptr<ParameterNode>> params,
                     TokenType returnType, std::vector<std::unique_ptr<ASTNode>> body,
                     std::unique_ptr<ReturnStatementNode> returnStmt)
        : name(std::move(name)), params(std::move(params)), returnType(returnType),
          body(std::move(body)), returnStmt(std::move(returnStmt)) {}

    ~FunctionDeclNode() noexcept override = default;

  private:
    std::string name;
    std::vector<std::unique_ptr<ParameterNode>> params;
    TokenType returnType;
    std::vector<std::unique_ptr<ASTNode>> body;
    std::unique_ptr<ReturnStatementNode> returnStmt;
};

} // namespace umbra

#endif // STATEMENTNODE_H