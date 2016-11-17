//
// Created by kagudkov on 12.11.16.
//

#pragma once
//реализация интерфейса обхода графа, создает дерево обхода для графвиза

#include <Visitors/IVisitor.h>
#include <Nodes/INode.h>
#include <vector>

#include <fstream>

class CValidateVisitor: public IVisitor {
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

};
