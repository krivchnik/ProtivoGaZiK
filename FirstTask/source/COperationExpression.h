#pragma once

#include "IExpression.h"


class COperationExpression: public IExpression {

public:

	enum OperationType { ADDITION, SUBTRACTION, MULTIPLICATION, DIVISON };

	COperationExpression(std::shared_ptr<IExpression> leftOperand_, std::shared_ptr<IExpression> rightOperand_, OperationType type_);
	std::shared_ptr<IExpression> GetLeftOperand();
	std::shared_ptr<IExpression> GetRightOperand();
	OperationType GetOperationType();

	void Accept(IVisitor*);

private:
	std::shared_ptr<IExpression> leftOperand;
	std::shared_ptr<IExpression> rightOperand;
	OperationType type;
};
