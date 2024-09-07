#ifndef VARIABLEDECLNODE_H
#define VARIABLEDECLNODE_H

#include "../../lexer/Tokens.h"
#include "../expressionnodes/ExpressionNode.h"
#include "StatementNode.h"
#include <memory>
#include <string>

namespace umbra {

class VariableDeclNode : public StatementNode {
  public:
    VariableDeclNode(TokenType type, const std::string &name,
                     std::unique_ptr<ExpressionNode> initializer = nullptr);

    TokenType getType() const { return type; }
    const std::string &getName() const { return name; }
    const ExpressionNode *getInitializer() const { return initializer.get(); }

    void accept(ASTVisitor &visitor) override;

  private:
    TokenType type;
    std::string name;
    std::unique_ptr<ExpressionNode> initializer;
};

} // namespace umbra

#endif // VARIABLEDECLNODE_H