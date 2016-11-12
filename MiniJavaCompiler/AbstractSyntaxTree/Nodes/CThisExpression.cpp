//
// Created by nismohl on 12.11.16.
//

#include <Nodes/CThisExpression.h>

void CThisExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}
