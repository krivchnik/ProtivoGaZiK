#pragma once

#include <Nodes/IExpression.h>

class CNumExpression: public IExpression {
public:
	CNumExpression(const Location location, int number);
	int GetNumber();

	void Accept(IVisitor*);
private:
	int number;
};
