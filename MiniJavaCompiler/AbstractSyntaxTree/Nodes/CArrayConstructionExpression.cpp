#include <Nodes/CArrayConstructionExpression.h>

CArrayConstructionExpression::CArrayConstructionExpression(const std::shared_ptr<IExpression> &size) : size(size) {}

const std::shared_ptr<IExpression> &CArrayConstructionExpression::getSize() const {
    return size;
}

void CArrayConstructionExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}