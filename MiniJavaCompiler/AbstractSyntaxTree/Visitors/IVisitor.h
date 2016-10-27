#pragma once
//Интерфейс обхода дерева разбора


//здесь объявления всех statement
class CAssignStatement;
class CCompoundStatement;
class CPrintStatement;
class CIfElseStatement;
class CWhileStatement;

//здесь объявления все expression
class CIdExpression;
class CNumExpression;
class COperationExpression;

class IVisitor {
public:

	virtual void Visit(CAssignStatement*) = 0;
	virtual void Visit(CCompoundStatement*) = 0;
	virtual void Visit(CPrintStatement*) = 0;
	virtual void Visit(CIfElseStatement*) = 0;
    virtual void Visit(CWhileStatement* ) = 0;

	virtual void Visit(CIdExpression*) = 0;
	virtual void Visit(CNumExpression*) = 0;
	virtual void Visit(COperationExpression*) = 0;
};
