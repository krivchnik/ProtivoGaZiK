#pragma once

#include "IStatement.h"

#include <memory>

class CAssignStatement: public IStatement {
public:
	CAssignStatement(std::shared_ptr<CIdExpression> variable, std::shared_ptr<COperandExpression> expression);
	std::shared_ptr<CIdExpression> GetVariable();
	std::shared_ptr<COperandExpression> GetExpression();

	void Accept(IVisitor*);
private:
	std::shared_ptr<CIdExpression> variable;
	std::shared_ptr<COperandExpression> expression;
};