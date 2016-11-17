//
// Created by nismohl on 12.11.16.
//

#include <Nodes/CListExpression.h>

CListExpression::CListExpression(const Location location, const std::string &expressionType)
        : expressionType(expressionType) {
    this->location = location;
}

void CListExpression::Add(std::shared_ptr<IExpression> Expression) {
    expressions.push_back(Expression);
}

const std::vector<std::shared_ptr<IExpression>> &CListExpression::GetExpressions() const {
    return expressions;
}

const std::string &CListExpression::GetExpressionType() const {
    return expressionType;
}

void CListExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}
