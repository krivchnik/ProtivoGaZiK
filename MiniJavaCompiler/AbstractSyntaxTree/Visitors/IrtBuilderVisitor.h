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

typedef typename std::unordered_map<std::string, std::shared_ptr<const IRTree::CStatement>> TMethodToIRTMap;

class CIrtBuilderVisitor: public IVisitor {
public:
    CIrtBuilderVisitor(const CSymbolTable& symbolTable)
            : symbolTable(symbolTable) {}

    TMethodToIRTMap GetMethodTrees();

    //принимает корень дерева и имя файла с выводом для графвиза
    void StartVisit(INode* startNode);
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

    template <class InputIteratorArguments, class InputIteratorLocals, class InputIteratorFields>
    void buildNewFrame( const std::string& className, const std::string& methodName,
                        InputIteratorArguments argumentsLeftIt, InputIteratorArguments argumentsRightIt,
                        InputIteratorLocals localsLeftIt, InputIteratorLocals localsRightIt,
                        InputIteratorFields fieldsLeftIt, InputIteratorFields fieldsRightIt );
    std::string makeMethodFullName( const std::string& className, const std::string& methodName );

    void buildNewFrame( CMethod* declaration );

    std::shared_ptr<IRTree::ISubtreeWrapper> subtreeWrapper;

    CSymbolTable symbolTable;

    std::string classCurrentName;
    std::unordered_map<std::string, std::shared_ptr<const IRTree::CFrame>> frames;
    IRTree::CFrame* frameCurrent;

    // used when translating expr.methodName() to determine the name of the class of expr
    std::string methodCallerClassName;

    // result
    TMethodToIRTMap methodTrees;
};
