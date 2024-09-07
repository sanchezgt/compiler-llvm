#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H

#include "../ASTNode.h"

namespace umbra {

class ExpressionNode : public ASTNode {
  public:
    virtual ~ExpressionNode() = default;
};

} // namespace umbra

#endif // EXPRESSIONNODE_H