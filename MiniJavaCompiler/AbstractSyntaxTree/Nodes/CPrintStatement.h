#pragma once

#include <Nodes/IStatement.h>
#include <Nodes/IExpression.h>

class CPrintStatement: public IStatement {
public:
	CPrintStatement(std::shared_ptr<IExpression> expressionArg);

	std::shared_ptr<IExpression> GetExpression();

	void Accept(IVisitor*);

private:
	std::shared_ptr<IExpression> expression;
};