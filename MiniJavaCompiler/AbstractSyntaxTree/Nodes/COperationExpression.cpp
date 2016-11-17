#include <Nodes/COperationExpression.h>

COperationExpression::COperationExpression(const Location location,
										   std::shared_ptr<IExpression> leftOperand,
										   std::shared_ptr<IExpression> rightOperand,
										   OperationType type)
		: leftOperand(leftOperand),
		  rightOperand(rightOperand),
		  type(type) {

	this->location = location;
}

std::shared_ptr<IExpression> COperationExpression::GetLeftOperand() {
	return leftOperand;
}

std::shared_ptr<IExpression> COperationExpression::GetRightOperand() {
	return rightOperand;
}

COperationExpression::OperationType COperationExpression::GetOperationType() {
	return type;
}

void COperationExpression::Accept(IVisitor* visitor) {
	visitor->Visit(this);
}


