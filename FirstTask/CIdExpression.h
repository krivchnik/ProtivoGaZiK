#pragma once

#include "IExpression.h"

#include <string>

class CIdExpression: public IExpression {
public:
	CIdExpression(std::string name);
	std::string GetName();
private:
	std::string name;
};