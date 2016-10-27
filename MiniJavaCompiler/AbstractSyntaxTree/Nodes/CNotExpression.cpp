#include <Nodes/CNotExpression.h>

CNotExpression::CNotExpression(std::shared_ptr<IExpression> exp_) :
        expression(exp_) {}

std::shared_ptr<IExpression> CNotExpression::GetExpression() {
    return expression;
}

void CNotExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}

