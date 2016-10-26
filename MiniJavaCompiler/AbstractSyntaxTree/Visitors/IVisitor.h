#pragma once


class CAssignStatement;
class CCompoundStatement;
class CPrintStatement;

class CIdExpression;
class CNumExpression;
class COperationExpression;
class CIfElseStatement;

class IVisitor {
public:

	virtual void Visit(CAssignStatement*) = 0;
	virtual void Visit(CCompoundStatement*) = 0;
	virtual void Visit(CPrintStatement*) = 0;

	virtual void Visit(CIdExpression*) = 0;
	virtual void Visit(CNumExpression*) = 0;
	virtual void Visit(COperationExpression*) = 0;
	virtual void Visit(CIfElseStatement*) = 0;
};
