#include "CAssignStatement.h"

CAssignStatement::CAssignStatement(std::shared_ptr<CIdExpression> variable_, std::shared_ptr<COperandExpression> expression_) :
	variable(variable_), expression(expression_) {}

std::shared_ptr<CIdExpression> CAssignStatement::GetVariable() {
	return variable;
}

std::shared_ptr<COperandExpression> CAssignStatement::GetExpression() {
	return expression;
}

void CAssignStatement::Accept(IVisitor* visitor) {
	visitor->Visit(this);
}