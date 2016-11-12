//
// Created by kagudkov on 12.11.16.
//

#ifndef MINIJAVACOMPILER_CGETCLASSESVISITOR_H
#define MINIJAVACOMPILER_CGETCLASSESVISITOR_H

#include <Visitors/IVisitor.h>
#include <string>
#include <set>

class CGetClassesVisitor : public IVisitor {

public:

    CGetClassesVisitor();

    std::set<std::string> getClasses() { return m_classes; }

    void Visit(CAssignStatement*) override;
    void Visit(CAssignItemStatement*) override;
    void Visit(CPrintStatement*) override;
    void Visit(CIfElseStatement*) override;
    void Visit(CWhileStatement*) override;
    void Visit(CListStatement*) override;

    void Visit(CVarDecl*) override;
    void Visit(CMethod*) override;
    void Visit(CClass*) override;
    void Visit(CMainClass*) override;
    void Visit(CProgram*) override;

    void Visit(CIdExpression*) override;
    void Visit(CNumExpression*) override;
    void Visit(CBoolExpression*) override;
    void Visit(CNotExpression*) override;
    void Visit(COperationExpression*) override;
    void Visit(CLengthExpression*) override;
    void Visit(CArrayConstructionExpression*) override;
    void Visit(CConstructClassExpression*) override;

private:
    std::set<std::string> m_classes;

};


#endif //MINIJAVACOMPILER_CGETCLASSESVISITOR_H
