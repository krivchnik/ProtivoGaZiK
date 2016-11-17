#include <Nodes/CArrayConstructionExpression.h>

CArrayConstructionExpression::CArrayConstructionExpression(const Location location, const std::shared_ptr<IExpression> &size)
        : size(size) {
    this->location = location;
}

const std::shared_ptr<IExpression> &CArrayConstructionExpression::getSize() const {
    return size;
}

void CArrayConstructionExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}