
#include <Visitors/CCheckTypesVisitor.h>
#include <CommonInclude.h>


void CCheckTypesVisitor::Visit(COperationExpression *expression) {

    expression->GetLeftOperand()->Accept(this);
    expression->GetRightOperand()->Accept(this);
}

void CCheckTypesVisitor::Visit(CNumExpression *expression) {
}

void CCheckTypesVisitor::Visit(CBoolExpression *expression) {
}

void CCheckTypesVisitor::Visit(CThisExpression *expression) {
}

void CCheckTypesVisitor::Visit(CIdExpression *expression) {
    std::string idType = getTypeFromId(expression->GetName());

    if(idType == NONE_TYPE) {
        //INKNOWN VARIABLE
        errors.AddError({expression->GetLocation(), ErrorType::UNDEFINED_VARIABLE, expression->GetName()});
    }
    expression->SetType(idType);
}

void CCheckTypesVisitor::Visit(CNotExpression *expression) {
    if(expression->GetType() != BOOLEAN_TYPE) {
        //!<exp>: <exp> MUST BE BOOLEAN
        errors.AddError({expression->GetLocation(), ErrorType::NON_BOOLEAN_EXP, expression->GetType()});
    }
    expression->GetExpression()->Accept(this);
}

void CCheckTypesVisitor::Visit(CLengthExpression *expression) {
    if(expression->GetType() != INT_ARRAY_TYPE) {
        //ONLY ARRAYS HAVE .length
        errors.AddError({expression->GetLocation(), ErrorType::NON_ARRAY, expression->GetType()});
    }
    expression->getExpression()->Accept(this);
}

void CCheckTypesVisitor::Visit(CArrayConstructionExpression *expression) {
    if(expression->getSize()->GetType() != INT_TYPE) {
        //SIZE OF ARRAY MUST BE INTEGER
        errors.AddError({expression->GetLocation(), ErrorType::NON_INTEGER, expression->GetType()});
    }
    expression->getSize()->Accept(this);

}


void CCheckTypesVisitor::Visit(CConstructClassExpression *expression) {
    if(classes.find(expression->GetType()) == classes.end()){
        //CAN'T CREATE OBJECT OF UNKNOWN CLASS
        errors.AddError({expression->GetLocation(), ErrorType::UNKNOWN_TYPE, expression->GetType()});
    }
}

void CCheckTypesVisitor::Visit(CAssignStatement *statement) {

    statement->GetVariable()->Accept(this);
    statement->GetExpression()->Accept(this);
}

void CCheckTypesVisitor::Visit(CAssignItemStatement *statement) {
    statement->getId()->Accept(this);
    statement->getExpressionInBrackets()->Accept(this);
    statement->getAssignedExpression()->Accept(this);
}

void CCheckTypesVisitor::Visit(CPrintStatement *statement) {
    statement->GetExpression()->Accept(this);
    auto expression = statement->GetExpression();
    if(expression->GetType() != INT_TYPE) {
        //ONLY ABLE TO PRINT INTEGERS
        errors.AddError({expression->GetLocation(), ErrorType::NON_INTEGER, expression->GetType()});
    }
}

void CCheckTypesVisitor::Visit(CIfElseStatement *statement) {
    statement->getExpression()->Accept(this);
    statement->getIfStatement()->Accept(this);
    statement->getElseStatement()->Accept(this);

    auto expression = statement->getExpression();
    if(expression->GetType() != BOOLEAN_TYPE) {
        //CONDITION MUST BE BOOLEAN
        errors.AddError({expression->GetLocation(), ErrorType::NON_BOOLEAN_EXP, expression->GetType()});
    }
}


void CCheckTypesVisitor::Visit(CWhileStatement *statement) {
    statement->getCondition()->Accept(this);
    statement->getBody()->Accept(this);

    auto expression = statement->getCondition();
    if(expression->GetType() != BOOLEAN_TYPE) {
        //CONDITION MUST BE BOOLEAN
        errors.AddError({expression->GetLocation(), ErrorType::NON_BOOLEAN_EXP, expression->GetType()});
    }
}

void CCheckTypesVisitor::Visit(CListStatement *statement) {
    auto statements = statement->GetStatements();
    size_t numberOfIterations = statements.size();
//    std::cout << "start analyze list of " << numberOfIterations << std::endl;

    for (size_t i = 0; i < numberOfIterations; ++i) {
        statements[i]->Accept(this);
    }
}

void CCheckTypesVisitor::Visit(CListExpression *statement) {

    auto statements = statement->GetExpressions();
    size_t numberOfIterations = statements.size();

    for (size_t i = 0; i < numberOfIterations; ++i) {
        statements[i]->Accept(this);
    }
}

void CCheckTypesVisitor::Visit(CVarDecl *decl) {
    //Проверка, что объявляемый тип существует.
    std::string typeName = decl->GetTypeName();
    if (types.find(typeName) == types.end() && classes.find(typeName) == classes.end()) {

        if (inMethodBody) {
            //UNKNOWN VAR TYPE IN METHOD BODY
            errors.AddError({decl->GetLocation(), ErrorType::UNKNOWN_TYPE, typeName});
        } else {
            //UNKNOWN VAR TYPE IN PARAM LIST
            errors.AddError({decl->GetLocation(), ErrorType::UNKNOWN_TYPE, typeName});
        }
    }
}

void CCheckTypesVisitor::Visit(CGetItemExpression *expression) {

    expression->GetObject()->Accept(this);
    expression->GetIndex()->Accept(this);
}

void CCheckTypesVisitor::Visit(CMethod *statement) {
    currentMethod = statement->getId()->GetName();
    statement->getId()->Accept(this);
    statement->getParameters()->Accept(this);

    inMethodBody = true;

    statement->getListDeclarations()->Accept(this);
    statement->getListStatements()->Accept(this);
    statement->getReturnExpression()->Accept(this);
    std::string typeName = statement->getTypeName();

    if (types.find(typeName) == types.end() && classes.find(typeName) == classes.end()) {
        //UNKNOWN RETURN TYPE
        errors.AddError({statement->getId()->GetLocation(), ErrorType::UNKNOWN_TYPE, typeName});
    }
    inMethodBody = false;
    currentMethod = "";
}


void CCheckTypesVisitor::Visit(CMethodCallExpression *exp) {
    //по сути имя класса вызывающего метод
    exp->SetType(NONE_TYPE);
    std::string className = exp->getObject()->GetType();

    if(classes.find(className) == classes.end()){
        //<CLASS>.method(): UNKNOWN <CLASS>
        errors.AddError({exp->getObject()->GetLocation(), ErrorType::UNKNOWN_TYPE, exp->getMethodId()->GetName()});
    } else {
        for(auto method : classes[className].methodsDeclarations) {
            if(method.name == exp->getMethodId()->GetName()) {
                if(method.visibility == "private" && className != currentClass) {
                    //PRIVATE METHOD CALL
                    errors.AddError({exp->getMethodId()->GetLocation(), ErrorType::PRIVATE_METHOD_CALL, method.name});
                }
            }
        }
    }

    exp->getObject()->Accept(this);
    exp->getMethodId()->Accept(this);
    exp->getArguments()->Accept(this);
}

void CCheckTypesVisitor::Visit(CClass *statement) {
    currentClass = statement->getId()->GetName();
    if (statement->getBaseId().get() != nullptr) {
        statement->getBaseId()->Accept(this);
    }
    statement->getFields()->Accept(this);
    statement->getMethods()->Accept(this);
    currentClass = "";
}


void CCheckTypesVisitor::Visit(CMainClass *statement) {
    currentClass = statement->GetClassId()->GetName();
    statement->GetClassId()->Accept(this);
    statement->GetArgId()->Accept(this);
    statement->GetStatement()->Accept(this);
    currentClass = "";
}


void CCheckTypesVisitor::Visit(CProgram *statement) {
    currentMethod = "";
    currentClass = "";
    statement->GetMainClass()->Accept(this);
    statement->GetMinorClasses()->Accept(this);
}

CCheckTypesVisitor::CCheckTypesVisitor(std::map<std::string, ClassInfo> &_classes) {
    classes = _classes;

    types["int"] = 0;
    types["intArray"] = 1;
    types["boolean"] = 2;
    inMethodBody = false;

}

std::vector<MethodInfo> CCheckTypesVisitor::getAvailableMethod() {

    if (currentClass == "") {
        return std::vector<MethodInfo>();
    }
    std::string nextClass = currentClass;
    std::vector<MethodInfo> availMethod = classes[nextClass].getPublicMethodsInfo();
    while (classes[nextClass].HasBase()) {
        nextClass = classes[nextClass].baseId;
        if (nextClass == currentClass) {
            break;
        }
        std::vector<MethodInfo> newMethod = classes[nextClass].getPublicMethodsInfo();
        for (auto iter = newMethod.begin(); iter != newMethod.end(); ++iter) {
            availMethod.push_back(*iter);
        }
    }
    return availMethod;
}

const std::string &CCheckTypesVisitor::getTypeFromId(std::string name) {
    //если в объявление класса
    for(auto iter = classes.begin(); iter != classes.end(); ++iter){
        if(iter->first == name) {
            return iter->first;
        }
    }

    //если это имя доступного метода
    std::vector<MethodInfo> availMethods = getAvailableMethod();
    for(int i = 0; i < availMethods.size(); ++i){
        if(availMethods[i].name == name){
            return availMethods[i].returnedType;
        }
    }

    //если поле класса
    for(auto field = classes[currentClass].variableDeclaration.begin();
        field != classes[currentClass].variableDeclaration.end(); ++field){
        if(field->name == name) {
            return field->type;
        }
    }
    //если поле предка
    std::string nextClassName = currentClass;
    while(classes[nextClassName].HasBase()){
        nextClassName = classes[nextClassName].baseId;
        if(currentClass == nextClassName){
            break;
        }
        for(auto field = classes[nextClassName].variableDeclaration.begin();
            field != classes[nextClassName].variableDeclaration.end(); ++field){
            if(field->name == name) {
                return field->type;
            }
        }
    }

    //если объявлено внутри метода
    if(inMethodBody){
        MethodInfo methodInfo;
        for(auto method = classes[currentClass].methodsDeclarations.begin();
                method != classes[currentClass].methodsDeclarations.end(); ++method) {
            if(method->name == currentMethod) {
                methodInfo = *method;
            }
        }
        for(auto param = methodInfo.paramList.begin(); param != methodInfo.paramList.end(); ++param){
            if(param -> name == name){
                return param->type;
            }
        }
        for(auto var = methodInfo.variablesList.begin(); var != methodInfo.variablesList.end(); ++var){
            if(var->name == name){
                return var->type;
            }
        }
    }

    return NONE_TYPE;

}

