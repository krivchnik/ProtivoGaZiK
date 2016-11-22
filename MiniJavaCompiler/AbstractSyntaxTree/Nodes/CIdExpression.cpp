#include <Nodes/CIdExpression.h>

CIdExpression::CIdExpression(const Location location, const std::string &name) {
    nameId = strings.add(name);
	this->typeId = nameId;
    this->location = location;
}

std::string CIdExpression::GetName() {
	return strings.get(nameId);
}

void CIdExpression::Accept(IVisitor* visitor) {
	visitor->Visit(this);
}