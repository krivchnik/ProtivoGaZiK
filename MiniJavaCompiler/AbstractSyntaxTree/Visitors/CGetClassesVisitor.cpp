//
// Created by kagudkov on 12.11.16.
//

#include <Visitors/CGetClassesVisitor.h>
#include <CommonInclude.h>

CGetClassesVisitor::CGetClassesVisitor()
{

}

void CGetClassesVisitor::Visit(COperationExpression* expression) {

    expression->GetLeftOperand()->Accept(this);
    expression->GetRightOperand()->Accept(this);
}

void CGetClassesVisitor::Visit(CNumExpression* expression) {
}

void CGetClassesVisitor::Visit(CBoolExpression* expression) {
}

void CGetClassesVisitor::Visit(CThisExpression* expression) {
}

void CGetClassesVisitor::Visit(CIdExpression* expression) {
}

void CGetClassesVisitor::Visit(CNotExpression* expression) {
    expression->GetExpression()->Accept(this);
}

void CGetClassesVisitor::Visit(CLengthExpression* expression) {
    expression->getExpression()->Accept(this);
}

void CGetClassesVisitor::Visit(CArrayConstructionExpression* expression) {
    expression->getSize()->Accept(this);

}


void CGetClassesVisitor::Visit(CConstructClassExpression* expression) {
}

void CGetClassesVisitor::Visit(CAssignStatement* statement) {
    statement->GetVariable()->Accept(this);
    statement->GetExpression()->Accept(this);
}

void CGetClassesVisitor::Visit(CAssignItemStatement* statement) {
    statement->getId()->Accept(this);
    statement->getExpressionInBrackets()->Accept(this);
    statement->getAssignedExpression()->Accept(this);
}

void CGetClassesVisitor::Visit(CPrintStatement* statement) {
    statement->GetExpression()->Accept(this);
}

void CGetClassesVisitor::Visit(CIfElseStatement* statement) {
    statement->getExpression()->Accept(this);
    statement->getIfStatement()->Accept(this);
    statement->getElseStatement()->Accept(this);
}


void CGetClassesVisitor::Visit(CWhileStatement* statement) {
    statement->getCondition()->Accept(this);
    statement->getBody()->Accept(this);
}

void CGetClassesVisitor::Visit(CListStatement* statement) {
    auto statements = statement->GetStatements();
    size_t numberOfIterations = statements.size();
    std::cout << "start analyze list of " << numberOfIterations << std::endl;

    for(size_t i = 0; i < numberOfIterations; ++i) {
        statements[i]->Accept(this);
    }
}

void CGetClassesVisitor::Visit(CListExpression* statement) {

    auto statements = statement->GetExpressions();
    size_t numberOfIterations = statements.size();

    for(size_t i = 0; i < numberOfIterations; ++i) {
        statements[i]->Accept(this);
    }
}

void CGetClassesVisitor::Visit(CVarDecl* decl) {
}

void CGetClassesVisitor::Visit(CGetItemExpression* expression) {

    expression->GetObject()->Accept(this);
    expression->GetIndex()->Accept(this);
}

void CGetClassesVisitor::Visit( CMethod* statement ) {

    statement->getId()->Accept(this);
    statement->getParameters()->Accept(this);
    statement->getListDeclarations()->Accept(this);
    statement->getListStatements()->Accept(this);
    statement->getReturnExpression()->Accept(this);
}


void CGetClassesVisitor::Visit( CMethodCallExpression* exp) {
    exp->getObject()->Accept(this);
    exp->getMethodId()->Accept(this);
    exp->getArguments()->Accept(this);
}

void CGetClassesVisitor::Visit( CClass* statement ) {
    std::cout << "start class visit ";
    ClassInfo classInfo;
    //classInfo.name = statement->getId()->GetName();
    if (statement->getBaseId().get() != nullptr) {
      //  classInfo.baseId = statement->getBaseId()->GetName();
        statement->getBaseId()->Accept(this);
    } else {
        classInfo.baseId = nullptr;
    }
//
//    for(auto field : statement->getFields()->GetStatements()) {
//        VariableInfo variableInfo;
//        variableInfo.name = dynamic_cast< CVarDecl* >(field.get())->GetVariableName();
//        variableInfo.type = dynamic_cast< CVarDecl* >(field.get())->GetTypeName();
//        classInfo.variableDeclaration.push_back(variableInfo);
//    }

    statement->getFields()->Accept(this);
/*
    for(auto methodFromList : statement->getMethods()->GetStatements()) {
        CMethod* method = dynamic_cast<CMethod* >(methodFromList.get());
        MethodInfo methodInfo;
        methodInfo.name = method->getId()->GetName();
        methodInfo.returnedType = method->getTypeName();
        for(auto param : method->getParameters()->GetStatements()) {
            VariableInfo paramInfo;
            paramInfo.name = dynamic_cast< CVarDecl* >(param.get())->GetVariableName();
            paramInfo.type = dynamic_cast< CVarDecl* >(param.get())->GetTypeName();
            methodInfo.paramList.push_back(paramInfo);
        }

        for(auto declFromList : method->getListDeclarations()->GetStatements()) {
            VariableInfo declInfo;
            CVarDecl* decl = dynamic_cast<CVarDecl* > (declFromList.get());
            declInfo.name = decl->GetVariableName();
            declInfo.type = decl->GetTypeName();
            methodInfo.variablesList.push_back(declInfo);
        }
        methodInfo.visibility = method->getVisibility();

        classInfo.methodsDeclarations.push_back(methodInfo);
    }
 */
    statement->getMethods()->Accept(this);
}


void CGetClassesVisitor::Visit( CMainClass* statement ) {
    statement->GetClassId()->Accept(this);
    statement->GetArgId()->Accept(this);
    statement->GetStatement()->Accept(this);
    std::cout << "MainClassAnalyzed" << std::endl;
}


void CGetClassesVisitor::Visit(CProgram *statement) {

    statement->GetMainClass()->Accept(this);
   // statement->GetMinorClasses()->Accept(this);
}






