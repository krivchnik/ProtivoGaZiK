#pragma once

#include <Nodes/IExpression.h>

#include <string>

class CIdExpression: public IExpression {
public:
	CIdExpression(const Location location, std::string name);
	std::string GetName();

	void Accept(IVisitor*);

	bool operator < (CIdExpression other) const {
		return name < other.name;
	}
private:
	std::string name;
};