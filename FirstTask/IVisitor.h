#pragma once

#include "CCompoundStatment.h"
#include "CAssignStatement.h"

#include "COperationExpression.h"
#include "CNumExpression.h"
#include "CIdExpression.h"

class IVistor {
public:

	virtual void visit(CCompoundStatement*) = 0;
	virtual void visit(CAssignStatement*) = 0;

	virtual void visit(COperationExpression*) = 0;
	virtual void visit(CNumExpression*) = 0;
	virtual void visit(CIdExpression*) = 0;
};
