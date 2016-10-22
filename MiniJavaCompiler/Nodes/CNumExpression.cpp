#include "CNumExpression.h"

CNumExpression::CNumExpression(int number_) :
	number(number_) {}

int CNumExpression::GetNumber() {
	return number;
}

void CNumExpression::Accept(IVisitor* visitor) {
	visitor->Visit(this);
}

