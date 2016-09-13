#pragma once

#include "IExpression.h"

class CNumExpression: public IExpression {
public:
	CNumExpression(int number);
	int GetNumber();
private:
	int number;
};
