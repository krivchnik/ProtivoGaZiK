#pragma once

#include <Nodes/IExpression.h>

class COperationExpression: public IExpression {

public:

	//WARNING: DON'T CHANGE ORDER!
	enum OperationType { ADDITION, SUBTRACTION, MULTIPLICATION, MOD, AND, OR, LESS };

	COperationExpression(const Location location,
						 std::shared_ptr<IExpression> leftOperand,
						 std::shared_ptr<IExpression> rightOperand,
						 OperationType operationType);

	std::shared_ptr<IExpression> GetLeftOperand();
	std::shared_ptr<IExpression> GetRightOperand();
	OperationType GetOperationType();

	void Accept(IVisitor*);

private:
	std::shared_ptr<IExpression> leftOperand;
	std::shared_ptr<IExpression> rightOperand;
	OperationType operationType;
};
