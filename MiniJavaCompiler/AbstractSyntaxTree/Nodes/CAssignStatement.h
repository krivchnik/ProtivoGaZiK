#pragma once

#include <Nodes/IStatement.h>
#include <Nodes/CIdExpression.h>
#include <Nodes/COperationExpression.h>

class CAssignStatement: public IStatement {
public:
	CAssignStatement(std::shared_ptr<CIdExpression> variable, std::shared_ptr<IExpression> expression);
	std::shared_ptr<CIdExpression> GetVariable();
	std::shared_ptr<IExpression> GetExpression();

	void Accept(IVisitor*);
private:
	std::shared_ptr<CIdExpression> variable;
	std::shared_ptr<IExpression> expression;
};