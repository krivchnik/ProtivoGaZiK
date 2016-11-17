#include <Nodes/CIdExpression.h>

CIdExpression::CIdExpression(const Location location, std::string name)
		: name(name) {
	this->location = location;
}

std::string CIdExpression::GetName() {
	return name;
}

void CIdExpression::Accept(IVisitor* visitor) {
	visitor->Visit(this);
}