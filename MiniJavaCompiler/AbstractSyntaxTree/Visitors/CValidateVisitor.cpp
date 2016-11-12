//
// Created by kagudkov on 12.11.16.
//

#include <Visitors/CValidateVisitor.h>

#include <CommonInclude.h>

void CValidateVisitor::StartVisit(INode *startNode, std::string filename) {

}

void CValidateVisitor::Visit(CAssignStatement *statement) {

    statement->GetVariable()->Accept(this);
    statement->GetExpression()->Accept(this);
}

void CValidateVisitor::Visit(CAssignItemStatement *statement) {

    statement->getId()->Accept(this);
    statement->getExpressionInBrackets()->Accept(this);
    statement->getAssignedExpression()->Accept(this);
}

void CValidateVisitor::Visit(CPrintStatement *statement) {
    statement->GetExpression()->Accept(this);
}

void CValidateVisitor::Visit(CIfElseStatement *statement) {

    statement->getExpression()->Accept(this);
    statement->getIfStatement()->Accept(this);
    statement->getElseStatement()->Accept(this);
}

void CValidateVisitor::Visit(CWhileStatement *statement) {

    statement->getCondition()->Accept(this);
    statement->getBody()->Accept(this);
}

void CValidateVisitor::Visit(CListStatement *statement) {

    auto statements = statement->GetStatements();
    size_t numberOfIterations = statements.size();

    for(size_t i = 0; i < numberOfIterations; ++i) {
        statements[i]->Accept(this);
    }
}

void CValidateVisitor::Visit(CListExpression *expression) {

    auto expressions = expression->GetExpressions();
    size_t numberOfIterations = expressions.size();

    for(size_t i = 0; i < numberOfIterations; ++i) {
        expressions[i]->Accept(this);
    }
}

void CValidateVisitor::Visit(CVarDecl *) {

}

void CValidateVisitor::Visit(CMethod *) {

}

void CValidateVisitor::Visit(CClass *) {

}

void CValidateVisitor::Visit(CMainClass *) {

}

void CValidateVisitor::Visit(CProgram *) {

}

void CValidateVisitor::Visit(CIdExpression *) {

}

void CValidateVisitor::Visit(CNumExpression *) {

}

void CValidateVisitor::Visit(CBoolExpression *) {

}

void CValidateVisitor::Visit(CNotExpression *) {

}

void CValidateVisitor::Visit(COperationExpression *expression) {

    expression->GetLeftOperand()->Accept(this);
    expression->GetRightOperand()->Accept(this);
}

void CValidateVisitor::Visit(CLengthExpression *) {

}

void CValidateVisitor::Visit(CArrayConstructionExpression *expression) {

    expression->getSize()->Accept(this);
}

void CValidateVisitor::Visit(CConstructClassExpression *) {

}

void CValidateVisitor::Visit(CMethodCallExpression *) {

}

void CValidateVisitor::Visit(CThisExpression *) {

}

void CValidateVisitor::Visit(CGetItemExpression *) {

}
