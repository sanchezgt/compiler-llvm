#ifndef STATEMENTNODE_H
#define STATEMENTNODE_H

#include "../ASTNode.h"

namespace umbra {

class StatementNode : public ASTNode {
  public:
    virtual ~StatementNode() = default;
};

} // namespace umbra

#endif // STATEMENTNODE_H