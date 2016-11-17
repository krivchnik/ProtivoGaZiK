//
// Created by kagudkov on 12.11.16.
//
#pragma once

#include <Visitors/IVisitor.h>
#include <Nodes/CClass.h>

#include <vector>
#include <string>
#include <set>
#include <map>

class CGetClassesVisitor : public IVisitor {

public:

    CGetClassesVisitor();

    std::map<std::shared_ptr<CIdExpression> , std::shared_ptr<CClass> > getClasses() { return classes; }

    void Visit(CAssignStatement*);
    void Visit(CAssignItemStatement*);
    void Visit(CPrintStatement*);
    void Visit(CIfElseStatement*);
    void Visit(CWhileStatement*);

    void Visit(CListStatement*);
    void Visit(CListExpression*);

    void Visit(CVarDecl*);
    void Visit(CMethod*);
    void Visit(CClass*);
    void Visit(CMainClass*);
    void Visit(CProgram*);

    void Visit(CIdExpression*);
    void Visit(CNumExpression*);
    void Visit(CBoolExpression*);
    void Visit(CNotExpression*);
    void Visit(COperationExpression*);
    void Visit(CLengthExpression*);
    void Visit(CArrayConstructionExpression*);
    void Visit(CConstructClassExpression*);
    void Visit(CMethodCallExpression*);
    void Visit(CThisExpression*);
    void Visit(CGetItemExpression*);

private:

    std::map<std::shared_ptr<CIdExpression> , std::shared_ptr<CClass> > classes;
};

