#pragma once
//реализация интерфейса обхода графа, создает дерево обхода для графвиза

#include <Visitors/IVisitor.h>
#include <Nodes/INode.h>
#include <vector>

#include <fstream>
#include <IRTree/SubtreeWrapper.h>
#include <IRTree/Frame.h>
#include "CInfoClasses.h"
#include "CSymbolTable.h"

class CIrtBuilderVisitor: public IVisitor {
public:
    //принимает корень дерева и имя файла с выводом для графвиза
    void StartVisit(INode* startNode, std::string filename);
    //Сюда нужно добавить методы visit для всех классов, которые мы хотим отображать в дереве.
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
    void updateSubtreeWrapper( IRTree::ISubtreeWrapper* wrapperNew );
    void updateSubtreeWrapper( std::shared_ptr<IRTree::ISubtreeWrapper> wrapperNew );
    std::string makeMethodFullName( const std::string& className, const std::string& methodName );

    void buildNewFrame( const CMethod* declaration );

    std::shared_ptr<IRTree::ISubtreeWrapper> subtreeWrapper;

    CSymbolTable symbolTable;

    std::string classCurrentName;
    std::unordered_map<std::string, std::shared_ptr<const IRTree::CFrame>> frames;
    IRTree::CFrame* frameCurrent;

    // used when translating expr.methodName() to determine the name of the class of expr
    std::string methodCallerClassName;




    int expressionId;
    //в этот вектор нужно добавить все имена токенов, которые мы хотим отрисовывать в форме прямоугольника, а не эллипса
    std::vector<std::string> idsOfTokenWithBoxShape;
    //При использовании графвиза у нас возникла проблема - разные с нашей точки зрения токены, имеющие одно и то же имя
    // сливались в одну ноду на дереве, моэтому после каждого токена мы пишем его id в формате tokenName + A + id
    // в качестве разделителя не получилось использовать " " |_ и тому подобные символы
    std::string delim = "A";

    std::ofstream file;
    //метод рисует стрелочку межда именами нод в файле вывода
    std::string getArrow() const;
    //метод заканчиват эту строку в файле вывода и переходит на следующую
    std::string getEndLine() const;

    std::string getNodeNameWithLabel(std::string label, int id, std::string nodeName ) const;
};
