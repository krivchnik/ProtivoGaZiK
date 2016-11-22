
#include <Visitors/CCheckTypesVisitor.h>
#include <CommonInclude.h>


void CCheckTypesVisitor::Visit(COperationExpression *expression) {

    auto leftOperand = expression->GetLeftOperand();
    auto rightOperand = expression->GetRightOperand();

    leftOperand->Accept(this);
    rightOperand->Accept(this);

    string typeLeft = leftOperand->GetType();
    string typeRight = rightOperand->GetType();
    string typeOperation = expression->GetType();

    if (typeLeft != typeOperation) {
        errors.push_back({leftOperand->GetLocation(), ErrorType::WRONG_TYPE, typeMismatch(typeLeft, typeOperation)});
    } else if (typeRight != typeOperation) {
        errors.push_back({rightOperand->GetLocation(), ErrorType::WRONG_TYPE, typeMismatch(typeRight, typeOperation)});
    }
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
        //UNKNOWN IDENTIFIER
        errors.push_back({expression->GetLocation(), ErrorType::UNDEFINED_IDENTIFIER, expression->GetName()});
    }
    expression->SetType(idType);
}

void CCheckTypesVisitor::Visit(CNotExpression *expression) {
    expression->GetExpression()->Accept(this);

    if(expression->GetType() != BOOLEAN_TYPE) {
        //!<exp>: <exp> MUST BE BOOLEAN
        errors.push_back({expression->GetLocation(), ErrorType::NON_BOOLEAN_EXP, expression->GetType()});
    }
}

void CCheckTypesVisitor::Visit(CLengthExpression *expression) {
    expression->getExpression()->Accept(this);

    if(expression->GetType() != INT_ARRAY_TYPE) {
        //ONLY ARRAYS HAVE .length
        errors.push_back({expression->GetLocation(), ErrorType::NON_ARRAY, expression->GetType()});
    }
}

void CCheckTypesVisitor::Visit(CArrayConstructionExpression *expression) { ;
    auto size = expression->getSize();
    size->Accept(this);

    if(size->GetType() != INT_TYPE) {
        //SIZE OF ARRAY MUST BE INTEGER
        errors.push_back({expression->GetLocation(), ErrorType::NON_INTEGER, size->GetType()});
    }
}

void CCheckTypesVisitor::Visit(CConstructClassExpression *expression) {
    if(classes.find(expression->GetType()) == classes.end()){
        //CAN'T CREATE OBJECT OF UNKNOWN CLASS
        errors.push_back({expression->GetLocation(), ErrorType::UNKNOWN_TYPE, expression->GetType()});
    }
}

void CCheckTypesVisitor::Visit(CAssignStatement *statement) {

    statement->GetVariable()->Accept(this);
    statement->GetExpression()->Accept(this);
}

void CCheckTypesVisitor::Visit(CAssignItemStatement *statement) {

    auto index = statement->getExpressionInBrackets();
    auto assignedExp = statement->getAssignedExpression();

    statement->getId()->Accept(this);
    index->Accept(this);
    assignedExp->Accept(this);

    string typeIndex = index->GetType();
    if (typeIndex != INT_TYPE) {
        //INDEX MUST BE INTEGER
        errors.push_back({index->GetLocation(), ErrorType::NON_INTEGER, index->GetType()});
    }

    if (assignedExp->GetType() != INT_TYPE) {
        //THERE ARE ONLY INT ARRAYS IN MINIJAVA, SO ASSIGNED EXP MUDT BE INT
        errors.push_back({index->GetLocation(), ErrorType::WRONG_TYPE, typeMismatch(assignedExp->GetType(), INT_TYPE)});
    }
}

void CCheckTypesVisitor::Visit(CPrintStatement *statement) {
    auto expression = statement->GetExpression();
    expression->Accept(this);
    if(expression->GetType() != INT_TYPE) {
        //ONLY ABLE TO PRINT INTEGERS
        errors.push_back({expression->GetLocation(), ErrorType::NON_INTEGER, expression->GetType()});
    }
}

void CCheckTypesVisitor::Visit(CIfElseStatement *statement) {
    statement->getExpression()->Accept(this);
    statement->getIfStatement()->Accept(this);
    statement->getElseStatement()->Accept(this);

    auto expression = statement->getExpression();
    if(expression->GetType() != BOOLEAN_TYPE) {
        //CONDITION MUST BE BOOLEAN
        errors.push_back({expression->GetLocation(), ErrorType::NON_BOOLEAN_EXP, expression->GetType()});
    }
}


void CCheckTypesVisitor::Visit(CWhileStatement *statement) {
    statement->getCondition()->Accept(this);
    statement->getBody()->Accept(this);

    auto expression = statement->getCondition();
    if(expression->GetType() != BOOLEAN_TYPE) {
        //CONDITION MUST BE BOOLEAN
        errors.push_back({expression->GetLocation(), ErrorType::NON_BOOLEAN_EXP, expression->GetType()});
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
            errors.push_back({decl->GetLocation(), ErrorType::UNKNOWN_TYPE, typeName});
        } else {
            //UNKNOWN VAR TYPE IN PARAM LIST
            errors.push_back({decl->GetLocation(), ErrorType::UNKNOWN_TYPE, typeName});
        }
    }
}

void CCheckTypesVisitor::Visit(CGetItemExpression *expression) {

    auto index = expression->GetIndex();
    expression->GetObject()->Accept(this);
    index->Accept(this);

    if (index->GetType() != INT_TYPE) {
        errors.push_back({index->GetLocation(), ErrorType::NON_INTEGER, index->GetType()});
    }

}

void CCheckTypesVisitor::Visit(CMethod *method) {
    currentMethod = method->getId()->GetName();

    //THERE ARE NO ERRORS IN MAIN METHOD PARAMS; MAIN METHOD IS ALSO PUBLIC
    if (!inMainMethodBody) {
        method->getId()->Accept(this);
        method->getParameters()->Accept(this);
    }

    inMethodBody = true;

    method->getListDeclarations()->Accept(this);
    method->getListStatements()->Accept(this);
    if (method->getReturnExpression() != nullptr) {
        method->getReturnExpression()->Accept(this);
    }

    std::string typeName = method->getTypeName();

    if (types.find(typeName) == types.end() && classes.find(typeName) == classes.end() && !inMainMethodBody) {
        //UNKNOWN RETURN TYPE
        errors.push_back({method->getId()->GetLocation(), ErrorType::UNKNOWN_TYPE, typeName});
    }
    inMethodBody = false;
    currentMethod = "";
}


void CCheckTypesVisitor::Visit(CMethodCallExpression *exp) {
    exp->getObject()->Accept(this);
    exp->getMethodId()->Accept(this);
    exp->getArguments()->Accept(this);

    //по сути имя класса вызывающего метод
    exp->SetType(NONE_TYPE);
    std::string className = exp->getObject()->GetType();

    if(classes.find(className) == classes.end()){
        //<CLASS>.method(): UNKNOWN <CLASS>
        errors.push_back({exp->getObject()->GetLocation(), ErrorType::UNKNOWN_TYPE, exp->getMethodId()->GetName()});
    } else {
        for(auto method : classes[className].methodsDeclarations) {
            if(method.name == exp->getMethodId()->GetName()) {
                if(method.visibility == "private" && className != currentClass) {
                    //PRIVATE METHOD CALL
                    errors.push_back({exp->getMethodId()->GetLocation(), ErrorType::PRIVATE_METHOD_CALL, method.name});
                }
            }
        }
    }
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
    inMainMethodBody = true;
    statement->GetMainMethod()->Accept(this);
    inMainMethodBody = false;
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
    inMainMethodBody = false;
    inMethodCallExpr = false;

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
    for(unsigned int i = 0; i < availMethods.size(); ++i){
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
            if(param->name == name) {
                return param->type;
            }
        }
        for(auto var = methodInfo.variablesList.begin(); var != methodInfo.variablesList.end(); ++var){
            if(var->name == name) {
                return var->type;
            }
        }
    }

    return NONE_TYPE;
}

std::string CCheckTypesVisitor::typeMismatch(std::string got, std::string expected) {
    std::string errorInfo = "got " + got + ", expected " + expected;
    return errorInfo;
}

