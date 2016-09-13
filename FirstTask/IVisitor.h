#pragma once

#include "CCompoundStatement.h"
#include "CAssignStatement.h"

#include "COperationExpression.h"
#include "CNumExpression.h"
#include "CIdExpression.h"

class IVisitor {
public:

	virtual void Visit(CCompoundStatement*) = 0;
	virtual void Visit(CAssignStatement*) = 0;

	virtual void Visit(COperationExpression*) = 0;
	virtual void Visit(CNumExpression*) = 0;
	virtual void Visit(CIdExpression*) = 0;
};
