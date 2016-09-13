#pragma once

#include "IStatement.h"

#include <memory>

class CCompoundStatement: public IStatement {
public:
	CCompoundStatement(std::shared_ptr<INode> leftOperand, std::shared_ptr<INode> rightOperand);
	std::shared_ptr<INode> GetLeftOperand();
	std::shared_ptr<INode> GetRightOperand();

private:
	std::shared_ptr<INode> leftOperand();
	std::shared_ptr<INode> rightOperand();	
}