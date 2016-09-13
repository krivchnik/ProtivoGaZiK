#pragma once

class CCompoundStatement;
class COperationExpression;
class CNumExpression;
class CAssignStatement;; 
class CIdExpression;

class IVisitor {
public:

	virtual void Visit(CCompoundStatement*) = 0;
	virtual void Visit(CAssignStatement*) = 0;

	virtual void Visit(COperationExpression*) = 0;
	virtual void Visit(CNumExpression*) = 0;
	virtual void Visit(CIdExpression*) = 0;
};
