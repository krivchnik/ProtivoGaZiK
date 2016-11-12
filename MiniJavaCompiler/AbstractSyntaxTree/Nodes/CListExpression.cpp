//
// Created by nismohl on 12.11.16.
//

#include <Nodes/CListExpression.h>

void CListExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}

void CListExpression::Add(std::shared_ptr<IExpression> Expression) {
    expressions.push_back(Expression);
}

const std::vector<std::shared_ptr<IExpression>> &CListExpression::GetExpressions() const {
    return expressions;
}

CListExpression::CListExpression(const std::string &expressionType)
        : expressionType(expressionType) {}

const std::string &CListExpression::GetExpressionType() const {
    return expressionType;
}
