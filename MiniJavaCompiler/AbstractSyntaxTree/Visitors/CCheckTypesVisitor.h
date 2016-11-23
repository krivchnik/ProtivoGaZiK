#pragma once

#include <Analyzer/Errors.h>

#include <Nodes/CClass.h>

#include <Visitors/CInfoClasses.h>
#include <Visitors/IVisitor.h>

#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>

class CCheckTypesVisitor : public IVisitor {

public:

    CCheckTypesVisitor(std::map<std::string, ClassInfo >& _classes);

    std::vector<ErrorDescription> GetErrors() const {
        return errors;
    }

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
    std::string methodCallClassName;
    //список методов доступных из текущего класса
    std::vector<MethodInfo> getAvailableMethodsInfo(std::string currentClass);

    //все классы-родители переданного класса
    std::vector<std::string> getAllBaseClasses(std::string className);

    //доступные типы
    std::map<std::string, int> types;

    std::vector<ErrorDescription> errors;

    //находимся ли мы уже в теле метода
    //Это нужно тк у нас нет класса Params. Чтобы определять ошибки в объявлениях параметров функции
    //или ошибки в объявлениях внутри метода
    bool inMethodBody;
    bool inMainMethodBody;
    bool inMethodCallExpr;

    const std::string &getTypeFromId(std::string basic_string);

    std::string getMismatchString(std::string got, std::string expected);
};


