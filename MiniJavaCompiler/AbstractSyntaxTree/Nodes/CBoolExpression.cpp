#include <Nodes/CBoolExpression.h>
#include "IStatement.h"

CBoolExpression::CBoolExpression(const Location location, bool value)
        : value(value) {
    this->location = location;
    this->typeId = BOOLEAN_TYPE;
}

bool CBoolExpression::GetValue() {
    return value;
}

void CBoolExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}

