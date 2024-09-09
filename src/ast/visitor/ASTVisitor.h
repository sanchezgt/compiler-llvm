#ifndef VISITOR_H
#define VISITOR_H

#include "../ASTNode.h"
#include "../ProgramNode.h"
#include "../expressionnodes/ExpressionNode.h"
#include "../statementnodes/StatementNode.h"

namespace umbra {

class ASTVisitor {
  public:
    virtual ~ASTVisitor() = default;

    virtual void visit(VariableDeclNode &node) = 0;
    virtual void visit(ProgramNode &node) = 0;
};

class PrintVisitor : public ASTVisitor {
  public:
    PrintVisitor();
    ~PrintVisitor() override;

    void visit(VariableDeclNode &node) override;
    void visit(ProgramNode &node) override;
    // Implement

  private:
    int indentLevel;
    void printIndent();
    void increaseIndent();
    void decreaseIndent();
};

} // namespace umbra

#endif // VISITOR_H