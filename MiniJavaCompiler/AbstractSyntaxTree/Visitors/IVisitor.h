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
class CListExpression;

class CVarDecl;
class CListVarDecl;
class CMethod;
class CListMethodDecl;
class CClass;
class CMainClass;
class CProgram;

//здесь объявления все expression
class CIdExpression;
class CBoolExpression;
class CNumExpression;
class CNotExpression;
class COperationExpression;
class CLengthExpression;
class CArrayConstructionExpression;
class CConstructClassExpression;
class CMethodCallExpression;
class CThisExpression;

class IVisitor {
public:

	virtual void Visit(CAssignStatement*) = 0;
    virtual void Visit(CAssignItemStatement*) = 0;
	virtual void Visit(CPrintStatement*) = 0;
	virtual void Visit(CIfElseStatement*) = 0;
    virtual void Visit(CWhileStatement*) = 0;

    virtual void Visit(CListStatement*) = 0;
    virtual void Visit(CListExpression*) = 0;

	virtual void Visit(CVarDecl*) = 0;
    virtual void Visit(CMethod*) = 0;
    virtual void Visit(CClass*) = 0;
	virtual void Visit(CMainClass*) = 0;
    virtual void Visit(CProgram*) = 0;

	virtual void Visit(CIdExpression*) = 0;
    virtual void Visit(CBoolExpression*) = 0;
	virtual void Visit(CNumExpression*) = 0;
    virtual void Visit(CNotExpression*) = 0;
	virtual void Visit(COperationExpression*) = 0;
    virtual void Visit(CLengthExpression*) = 0;
    virtual void Visit(CArrayConstructionExpression*) = 0;
	virtual void Visit(CConstructClassExpression*) = 0;
    virtual void Visit(CMethodCallExpression*) = 0;
    virtual void Visit(CThisExpression*) = 0;
};
