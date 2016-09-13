#include "COperationExpression.h"

COperationExpression::COperationExpression(std::shared_ptr<IExpression> leftOperand_, std::shared_ptr<IExpression> rightOperand_, OperationType type_) :
	leftOperand(leftOperand_), rightOperand(rightOperand_), type(type_) {}

std::shared_ptr<IExpression> COperationExpression::GetLeftOperand() {
	return leftOperand;
}

std::shared_ptr<IExpression> COperationExpression::GetRightOperand() {
	return rightOperand;
}

OperationType COperationExpression::GetOperationType() {
	return type;
}

void COperationExpression::Accept(IVisitor* visitor) {
	visitor->Visit(this);
}


