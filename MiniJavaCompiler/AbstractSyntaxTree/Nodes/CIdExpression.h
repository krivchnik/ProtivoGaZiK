#pragma once

#include <Nodes/IExpression.h>

#include <string>

class CIdExpression: public IExpression {
public:
	CIdExpression(const Location location, const std::string &name);
	std::string GetName();
	int getNameId() { return nameId; }

	void Accept(IVisitor*);

	bool operator < (CIdExpression other) const {
		return strings.get(nameId) < strings.get(other.nameId);
	}
private:
	int nameId;
};