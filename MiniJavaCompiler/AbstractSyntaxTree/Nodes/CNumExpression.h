#pragma once

#include <Nodes/IExpression.h>

class CNumExpression: public IExpression {
public:
	CNumExpression(int number);
	int GetNumber();

	void Accept(IVisitor*);
private:
	int number;
};
