#include <Nodes/CPrintStatement.h>

CPrintStatement::CPrintStatement(const Location location, std::shared_ptr<IExpression> expression)
		: expression(expression) {

	this->location = location;
}

void CPrintStatement::Accept(IVisitor* visitor) {
	visitor->Visit(this);
}

std::shared_ptr<IExpression> CPrintStatement::GetExpression() {
	return expression;
}