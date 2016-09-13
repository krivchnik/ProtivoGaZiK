#pragma once

#include "IExpression.h"

class CNumExpression: public IExpression {
public:
	CNumExpression(int number);
	int GetNumber();

	void Accept(IVisitor*);
private:
	int number;
};
