#include <Nodes/CIdExpression.h>

CIdExpression::CIdExpression(std::string name_) :
	name(name_) {}

std::string CIdExpression::GetName() {
	return name;
}

void CIdExpression::Accept(IVisitor* visitor) {
	visitor->Visit(this);
}