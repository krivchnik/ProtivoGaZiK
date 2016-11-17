#include <Nodes/CAssignItemStatement.h>

CAssignItemStatement::CAssignItemStatement(const Location location,
                                           std::shared_ptr<CIdExpression> id,
                                           std::shared_ptr<IExpression> expressionInBrackets,
                                           std::shared_ptr<IExpression> assignedExpression)
        : id(id),
          expressionInBrackets(expressionInBrackets),
          assignedExpression(assignedExpression) {
    this->location = location;
}

std::shared_ptr<CIdExpression> CAssignItemStatement::getId() {
    return id;
}

std::shared_ptr<IExpression> CAssignItemStatement::getExpressionInBrackets() {
    return expressionInBrackets;
}

std::shared_ptr<IExpression> CAssignItemStatement::getAssignedExpression() {
    return assignedExpression;
}

void CAssignItemStatement::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}