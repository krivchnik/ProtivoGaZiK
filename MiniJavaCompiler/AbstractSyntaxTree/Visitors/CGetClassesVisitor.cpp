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
//    std::cout << "start analyze list of " << numberOfIterations << std::endl;

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
    if (statement->getReturnExpression() != nullptr) {
        statement->getReturnExpression()->Accept(this);
    }
}


void CGetClassesVisitor::Visit( CMethodCallExpression* exp) {
    exp->getObject()->Accept(this);
    exp->getMethodId()->Accept(this);
    exp->getArguments()->Accept(this);
}

void CGetClassesVisitor::Visit( CClass* statement ) {
    ClassInfo classInfo;
    classInfo.name = statement->getId()->GetName();
    classInfo.location = statement->GetLocation();

    if (statement->getBaseId().get() != nullptr) {
        classInfo.baseId = statement->getBaseId()->GetName();
        statement->getBaseId()->Accept(this);
    } else {
        classInfo.baseId = "";
    }

    for(auto field : statement->getFields()->GetStatements()) {
        VariableInfo variableInfo;
        CVarDecl* decl = dynamic_cast< CVarDecl* >(field.get());
        variableInfo.location = decl->GetLocation();
        variableInfo.name = decl->GetVariableName();
        variableInfo.type = decl->GetTypeName();
        classInfo.variableDeclaration.push_back(variableInfo);
    }

    statement->getFields()->Accept(this);

    for(auto methodFromList : statement->getMethods()->GetStatements()) {
        CMethod* method = dynamic_cast<CMethod* >(methodFromList.get());
        MethodInfo methodInfo;
        methodInfo.name = method->getId()->GetName();
        methodInfo.returnedType = method->getTypeName();
        methodInfo.visibility = method->getVisibility();
        methodInfo.location = method->GetLocation();

        for(auto param : method->getParameters()->GetStatements()) {
            VariableInfo paramInfo;
            CVarDecl* decl = dynamic_cast< CVarDecl* >(param.get());
            paramInfo.name = decl->GetVariableName();
            paramInfo.type = decl->GetTypeName();
            paramInfo.location = decl->GetLocation();
            methodInfo.paramList.push_back(paramInfo);
        }

        for(auto declFromList : method->getListDeclarations()->GetStatements()) {
            VariableInfo declInfo;
            CVarDecl* decl = dynamic_cast<CVarDecl* > (declFromList.get());
            declInfo.name = decl->GetVariableName();
            declInfo.type = decl->GetTypeName();
            declInfo.location = decl->GetLocation();
            methodInfo.variablesList.push_back(declInfo);
        }

        classInfo.methodsDeclarations.push_back(methodInfo);
    }
    if( classes.find(classInfo.name) == classes.end() ) {
        classes[classInfo.name] = classInfo;
    } else {
        errors.push_back({statement->GetLocation(), ErrorType::REDEFINITION_CLASS, statement->getId()->GetName()});
    }
    statement->getMethods()->Accept(this);
}


void CGetClassesVisitor::Visit( CMainClass* statement ) {
    ClassInfo classInfo;
    classInfo.name = statement->GetClassId()->GetName();
    classInfo.baseId = "";
    classInfo.location = statement->GetLocation();

    auto params = statement->GetMainMethod()->getParameters()->GetStatements();
    CVarDecl* decl = dynamic_cast<CVarDecl* >(params[0].get());

    VariableInfo paramInfo;
    paramInfo.name = decl->GetVariableName();
    paramInfo.location = decl->GetLocation();
    paramInfo.type = decl->GetTypeName();

    auto method = statement->GetMainMethod();
    MethodInfo methodInfo;
    methodInfo.location = method->GetLocation();
    methodInfo.name = method->getId()->GetName();
    methodInfo.returnedType = method->getTypeName();
    methodInfo.visibility = method->getVisibility();
    methodInfo.paramList.push_back(paramInfo);

    classInfo.methodsDeclarations.push_back(methodInfo);

    if(classes.find(classInfo.name) == classes.end()){
        classes[classInfo.name] = classInfo;
    } else {
        errors.push_back({statement->GetLocation(), ErrorType::REDEFINITION_CLASS, statement->GetClassId()->GetName()});
    }
    statement->GetClassId()->Accept(this);
    statement->GetMainMethod()->Accept(this);
}


void CGetClassesVisitor::Visit(CProgram *statement) {

    statement->GetMainClass()->Accept(this);
    statement->GetMinorClasses()->Accept(this);
}
