#include <Nodes/CNumExpression.h>

CNumExpression::CNumExpression(const Location location, int number)
		: number(number) {
	this->location = location;
}

int CNumExpression::GetNumber() {
	return number;
}

void CNumExpression::Accept(IVisitor* visitor) {
	visitor->Visit(this);
}

