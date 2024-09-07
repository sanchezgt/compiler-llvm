#include "VariableDecNode.h"
#include "../visitor/ASTVisitor.h"

namespace umbra {

VariableDeclNode::VariableDeclNode(TokenType type, const std::string &name,
                                   std::unique_ptr<ExpressionNode> initializer)
    : type(type), name(name), initializer(std::move(initializer)) {}

void VariableDeclNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

} // namespace umbra