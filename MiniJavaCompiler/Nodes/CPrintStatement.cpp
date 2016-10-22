#include "CPrintStatement.h"

CPrintStatement::CPrintStatement(std::shared_ptr<IExpression> expressionArg) :
	expression(expressionArg) {}

void CPrintStatement::Accept(IVisitor* visitor) {
	visitor->Visit(this);
}

std::shared_ptr<IExpression> CPrintStatement::GetExpression() {
	return expression;
}