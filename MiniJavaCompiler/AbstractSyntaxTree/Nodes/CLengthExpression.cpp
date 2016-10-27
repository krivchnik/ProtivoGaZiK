//
// Created by kagudkov on 27.10.16.
//

#include <Nodes/CLengthExpression.h>

CLengthExpression::CLengthExpression(std::shared_ptr<IExpression> expression) : expression(expression) {}

std::shared_ptr<IExpression> CLengthExpression::getExpression() {
    return expression;
}


void CLengthExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}