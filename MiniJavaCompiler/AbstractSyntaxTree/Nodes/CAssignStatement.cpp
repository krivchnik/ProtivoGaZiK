#include <Nodes/CAssignStatement.h>

CAssignStatement::CAssignStatement(const Location location,
								   std::shared_ptr<CIdExpression> variable_,
								   std::shared_ptr<IExpression> expression_)
		: variable(variable_),
		  expression(expression_) {
	this->location = location;
}

std::shared_ptr<CIdExpression> CAssignStatement::GetVariable() {
	return variable;
}

std::shared_ptr<IExpression> CAssignStatement::GetExpression() {
	return expression;
}

void CAssignStatement::Accept(IVisitor* visitor) {
	visitor->Visit(this);
}