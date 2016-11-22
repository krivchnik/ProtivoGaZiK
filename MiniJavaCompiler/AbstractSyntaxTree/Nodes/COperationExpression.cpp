#include <Nodes/COperationExpression.h>

COperationExpression::COperationExpression(const Location location,
										   std::shared_ptr<IExpression> leftOperand,
										   std::shared_ptr<IExpression> rightOperand,
										   OperationType operationType)
		: leftOperand(leftOperand),
		  rightOperand(rightOperand),
		  operationType(operationType) {

	this->location = location;
    type = (operationType >= 4) ? BOOLEAN_TYPE : INT_TYPE;
}

std::shared_ptr<IExpression> COperationExpression::GetLeftOperand() {
	return leftOperand;
}

std::shared_ptr<IExpression> COperationExpression::GetRightOperand() {
	return rightOperand;
}

COperationExpression::OperationType COperationExpression::GetOperationType() {
	return operationType;
}

void COperationExpression::Accept(IVisitor* visitor) {
	visitor->Visit(this);
}
