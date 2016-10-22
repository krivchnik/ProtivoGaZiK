#pragma once

#include <Nodes/IStatement.h>

class CCompoundStatement: public IStatement {
public:
	CCompoundStatement(std::shared_ptr<INode> leftOperand, std::shared_ptr<INode> rightOperand);
	std::shared_ptr<INode> GetLeftOperand();
	std::shared_ptr<INode> GetRightOperand();

	void Accept(IVisitor*);

private:
	std::shared_ptr<INode> leftOperand;
	std::shared_ptr<INode> rightOperand;	
};