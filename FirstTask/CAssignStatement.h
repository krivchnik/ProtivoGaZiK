#pragma once

#include "IStatement.h"
#include "CIdExpression.h"
#include "COperationExpression.h"

#include <memory>

class CAssignStatement: public IStatement {
public:
	CAssignStatement(std::shared_ptr<CIdExpression> variable, std::shared_ptr<COperationExpression> expression);
	std::shared_ptr<CIdExpression> GetVariable();
	std::shared_ptr<COperationExpression> GetExpression();

	void Accept(IVisitor*);
private:
	std::shared_ptr<CIdExpression> variable;
	std::shared_ptr<COperandExpression> expression;
};