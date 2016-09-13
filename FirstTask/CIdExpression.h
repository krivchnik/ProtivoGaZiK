#pragma once

#include "IExpression.h"

#include <string>

class CIdExpression: public IExpression {
public:
	CIdExpression(std::string name);
	std::string GetName();

	void Accept(IVisitor*)
private:
	std::string name;
};