#include <Nodes/CNumExpression.h>

CNumExpression::CNumExpression(const Location location, int number)
		: number(number) {
	this->location = location;
	this->typeId = INT_TYPE;
}

int CNumExpression::GetNumber() {
	return number;
}

void CNumExpression::Accept(IVisitor* visitor) {
	visitor->Visit(this);
}

