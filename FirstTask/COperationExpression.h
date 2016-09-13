#pragma once

#include "IExpression.h"

#include <memory>

enum OperationType {
	'+', '-', '*', ':'
};

class COperationExpression: public IExpression {
public:
	COperationExpression(std::shared_ptr<IExpression> leftOperand_, std::shared_ptr<IExpression> rightOperand_, OperandType type_);
	std::shared_ptr<IExpression> GetLeftOperand();
	std::shared_ptr<IExpression> GetRightOperand();
	OperandType GetOperationType();

private:
	std::shared_ptr<IExpression> leftOperand;
	std::shared_ptr<IExpression> rightOperand;
	OperationType type;
};
