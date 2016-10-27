#include <Nodes/CAssignItemStatement.h>

CAssignItemStatement::CAssignItemStatement(std::shared_ptr<CIdExpression> id,
                                           std::shared_ptr<IExpression> expressionInBrackets,
                                           std::shared_ptr<IExpression> assignedExpression) : id(id),
                                                                                                     expressionInBrackets(
                                                                                                             expressionInBrackets),
                                                                                                     assignedExpression(
                                                                                                             assignedExpression) {}

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