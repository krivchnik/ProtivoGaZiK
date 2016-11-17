//
// Created by kagudkov on 12.11.16.
//

#include <Visitors/CValidateVisitor.h>

#include <CommonInclude.h>

void CValidateVisitor::StartVisit(INode *startNode, std::string filename) {

}

void CValidateVisitor::Visit(COperationExpression* expression) {

    expression->GetLeftOperand()->Accept(this);
    expression->GetRightOperand()->Accept(this);
}

void CValidateVisitor::Visit(CNumExpression* expression) {
}

void CValidateVisitor::Visit(CBoolExpression* expression) {
}

void CValidateVisitor::Visit(CThisExpression* expression) {
}

void CValidateVisitor::Visit(CIdExpression* expression) {
}

void CValidateVisitor::Visit(CNotExpression* expression) {
    expression->GetExpression()->Accept(this);
}

void CValidateVisitor::Visit(CLengthExpression* expression) {
    expression->getExpression()->Accept(this);
}

void CValidateVisitor::Visit(CArrayConstructionExpression* expression) {
    expression->getSize()->Accept(this);
}

void CValidateVisitor::Visit(CConstructClassExpression* expression) {
}

void CValidateVisitor::Visit(CAssignStatement* statement) {
    statement->GetVariable()->Accept(this);
    statement->GetExpression()->Accept(this);
}

void CValidateVisitor::Visit(CAssignItemStatement* statement) {
    statement->getId()->Accept(this);
    statement->getExpressionInBrackets()->Accept(this);
    statement->getAssignedExpression()->Accept(this);
}

void CValidateVisitor::Visit(CPrintStatement* statement) {
    statement->GetExpression()->Accept(this);
}

void CValidateVisitor::Visit(CIfElseStatement* statement) {
    statement->getExpression()->Accept(this);
    statement->getIfStatement()->Accept(this);
    statement->getElseStatement()->Accept(this);
}


void CValidateVisitor::Visit(CWhileStatement* statement) {
    statement->getCondition()->Accept(this);
    statement->getBody()->Accept(this);
}

void CValidateVisitor::Visit(CListStatement* statement) {

    auto statements = statement->GetStatements();
    size_t numberOfIterations = statements.size();

    for(size_t i = 0; i < numberOfIterations; ++i) {
        if (i != numberOfIterations - 1) {
            statements[i]->Accept(this);
        } else {
            statements[numberOfIterations - 1]->Accept(this);
        }
    }
}

void CValidateVisitor::Visit(CListExpression* statement) {

    auto statements = statement->GetExpressions();
    size_t numberOfIterations = statements.size();

    for(size_t i = 0; i < numberOfIterations; ++i) {
        if (i != numberOfIterations - 1) {
            statements[i]->Accept(this);
        } else {
            statements[numberOfIterations - 1]->Accept(this);
        }
    }
}

void CValidateVisitor::Visit(CVarDecl* decl) {

}

void CValidateVisitor::Visit(CGetItemExpression* expression) {

    expression->GetObject()->Accept(this);
    expression->GetIndex()->Accept(this);
}

void CValidateVisitor::Visit( CMethod* statement ) {

    statement->getId()->Accept(this);
    statement->getParameters()->Accept(this);
    statement->getListDeclarations()->Accept(this);
    statement->getListStatements()->Accept(this);
    statement->getReturnExpression()->Accept(this);
}


void CValidateVisitor::Visit( CMethodCallExpression* exp) {
    exp->getObject()->Accept(this);
    exp->getMethodId()->Accept(this);
    exp->getArguments()->Accept(this);
}

void CValidateVisitor::Visit( CClass* statement ) {
    statement->getId()->Accept(this);
    if (statement->getBaseId().get() != nullptr) {
        statement->getBaseId()->Accept(this);
    }

    statement->getFields()->Accept(this);
    statement->getMethods()->Accept(this);
}


void CValidateVisitor::Visit( CMainClass* statement ) {
    statement->GetClassId()->Accept(this);
    statement->GetArgId()->Accept(this);
    statement->GetStatement()->Accept(this);
}


void CValidateVisitor::Visit(CProgram *statement) {

    statement->GetMainClass()->Accept(this);
    statement->GetMinorClasses()->Accept(this);
}