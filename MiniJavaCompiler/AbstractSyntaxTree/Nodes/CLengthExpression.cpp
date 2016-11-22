//
// Created by kagudkov on 27.10.16.
//

#include <Nodes/CLengthExpression.h>
#include "IStatement.h"

CLengthExpression::CLengthExpression(const Location location,
                                     std::shared_ptr<IExpression> expression)
        : expression(expression) {
    this->location = location;
    this->typeId = INT_TYPE;
}

std::shared_ptr<IExpression> CLengthExpression::getExpression() {
    return expression;
}


void CLengthExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}