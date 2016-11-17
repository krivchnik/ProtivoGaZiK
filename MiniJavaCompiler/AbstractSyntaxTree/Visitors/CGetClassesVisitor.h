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

struct VariableInfo{
    std::string type;
    std::string name;
};

struct MethodInfo{
    std::string returnedType;
    std::string name;
    std::vector<VariableInfo> paramList;
    std::vector<VariableInfo> variablesList;
    std::string visibility;
};

struct ClassInfo{
   std::vector<MethodInfo> methodsDeclarations;
   std::vector<VariableInfo> variableDeclaration;
   std::string baseId;
   std::string name;
};


class CGetClassesVisitor : public IVisitor {

public:

    CGetClassesVisitor();

    std::map< std::string, ClassInfo > getClasses() { return classes; }
    //если увидим ещё раз класс с тем же именем, то препишем его уже существующему CIdExpression;
    std::map<std::string, std::shared_ptr<CIdExpression> > classesNames;
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

    std::map< std::string, ClassInfo > classes;

};

