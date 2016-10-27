#pragma once
//Интерфейс обхода дерева разбора


//здесь объявления всех statement
class CAssignStatement;
class CAssignItemStatement;
class CCompoundStatement;
class CPrintStatement;
class CIfElseStatement;
class CWhileStatement;
class CListStatement;

//здесь объявления все expression
class CIdExpression;
class CBoolExpression;
class CNumExpression;
class CNotExpression;
class COperationExpression;
class CLengthExpression;

class IVisitor {
public:

	virtual void Visit(CAssignStatement*) = 0;
    virtual void Visit(CAssignItemStatement*) = 0;
    virtual void Visit(CCompoundStatement*) = 0;
	virtual void Visit(CPrintStatement*) = 0;
	virtual void Visit(CIfElseStatement*) = 0;
    virtual void Visit(CWhileStatement*) = 0;
    virtual void Visit(CListStatement*) = 0;

	virtual void Visit(CIdExpression*) = 0;
    virtual void Visit(CBoolExpression*) = 0;
	virtual void Visit(CNumExpression*) = 0;
    virtual void Visit(CNotExpression*) = 0;
	virtual void Visit(COperationExpression*) = 0;
    virtual void Visit(CLengthExpression*) = 0;

};
