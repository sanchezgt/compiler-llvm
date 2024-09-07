#ifndef VISITOR_H
#define VISITOR_H

#include "../ASTNode.h"
#include "../expressionnodes/ExpressionNode.h"
#include "../statementnodes/StatementNode.h"
#include "../statementnodes/VariableDecNode.h"

namespace umbra {

class ASTVisitor {
  public:
    virtual ~ASTVisitor() = default;

    virtual void visit(VariableDeclNode &node) = 0;
    // Add more visit methods for other node types as you implement them
    // For example:
    // virtual void visit(BinaryExpressionNode& node) = 0;
    // virtual void visit(IfStatementNode& node) = 0;
};

class PrintVisitor : public ASTVisitor {
  public:
    PrintVisitor();

    void visit(VariableDeclNode &node) override;
    // Implement other visit methods as you add more node types

  private:
    int indentLevel;
    void printIndent();
    void increaseIndent();
    void decreaseIndent();
};

} // namespace umbra

#endif // VISITOR_H