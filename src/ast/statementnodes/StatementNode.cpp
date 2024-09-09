#include "StatementNode.h"

#include "../expressionnodes/ExpressionNode.h"
#include "../visitor/ASTVisitor.h"
#include <memory>
#include <string>

namespace umbra {

VariableDeclNode::VariableDeclNode(TokenType type, const std::string &name,
                                   std::unique_ptr<ExpressionNode> initializer)
    : type(type), name(name), initializer(std::move(initializer)) {}

void VariableDeclNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

} // namespace umbra