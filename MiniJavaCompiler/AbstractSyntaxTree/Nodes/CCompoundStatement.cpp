#include <Nodes/CCompoundStatement.h>

CCompoundStatement::CCompoundStatement(std::shared_ptr<INode> leftOperand_, std::shared_ptr<INode> rightOperand_) :
	leftOperand(leftOperand_), rightOperand(rightOperand_) {}

std::shared_ptr<INode> CCompoundStatement::GetLeftOperand() {
	return leftOperand;
}

std::shared_ptr<INode> CCompoundStatement::GetRightOperand() {
	return rightOperand;
}

void CCompoundStatement::Accept(IVisitor* visitor) {
	visitor->Visit(this);
}