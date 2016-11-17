//
// Created by nismohl on 12.11.16.
//

#include <Nodes/CThisExpression.h>

CThisExpression::CThisExpression(const Location location) {
    this->location = location;
}

void CThisExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}
