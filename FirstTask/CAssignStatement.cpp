#include "CAssignStatement.h"

CAssignStatement::CAssignStatement(std::shared_ptr<CIdExpression> variable_, std::shared_ptr<COperationExpression> expression_) :
	variable(variable_), expression(expression_) {}

std::shared_ptr<CIdExpression> CAssignStatement::GetVariable() {
	return variable;
}

std::shared_ptr<COperationExpression> CAssignStatement::GetExpression() {
	return expression;
}

void CAssignStatement::Accept(IVisitor* visitor) {
	visitor->Visit(this);
}