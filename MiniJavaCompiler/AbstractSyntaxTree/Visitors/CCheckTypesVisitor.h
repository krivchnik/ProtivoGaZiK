#pragma once

#include <Visitors/IVisitor.h>
#include <Nodes/CClass.h>
#include <Visitors/CInfoClasses.h>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <ostream>


class CCheckTypesVisitor : public IVisitor {

public:

    CCheckTypesVisitor(std::map<std::string, ClassInfo >& _classes);

    //если увидим ещё раз класс с тем же именем, то препишем его уже существующему CIdExpression;
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
    //если текущее положение вне класса или метода, то будет = ""
    std::string currentClass;
    std::string currentMethod;
    //список методов доступных из текущего класса
    std::set<std::string> getAvailableMethod();
    //доступные типы
    std::map<std::string, int> types;

    //находимся ли мы уже в теле метода
    //Это нужно тк у нас нет класса Params. Чтобы определять ошибки в объявлениях параметров функции
    //или ошибки в объявлениях внутри метода
    bool inMethodBody;
};


