#include <Nodes/CNotExpression.h>

CNotExpression::CNotExpression(const Location location, std::shared_ptr<IExpression> expression)
        : expression(expression) {
    this->location = location;
    this->type = BOOLEAN_TYPE;
}

std::shared_ptr<IExpression> CNotExpression::GetExpression() {
    return expression;
}

void CNotExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}

