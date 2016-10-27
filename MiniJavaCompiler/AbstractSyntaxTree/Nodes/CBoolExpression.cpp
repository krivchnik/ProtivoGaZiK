#include <Nodes/CBoolExpression.h>

CBoolExpression::CBoolExpression(bool value_) :
        value(value_) {}

bool CBoolExpression::GetValue() const {
    return value;
}

void CBoolExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}

