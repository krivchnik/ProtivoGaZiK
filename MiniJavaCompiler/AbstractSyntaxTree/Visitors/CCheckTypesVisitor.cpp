
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
    //если не было определения у переменной, но она используется
    if(idType == NONE_TYPE){
        std::cout << "use undefined variable " << expression->GetName() + "::" + currentClass
                                                  + "::" + currentMethod<< endl;
    }
    expression->setType(idType);
}

void CCheckTypesVisitor::Visit(CNotExpression *expression) {
    if(expression->getType() != BOOLEAN_TYPE) {
        std::cout << "try use not to " << expression->getType() << endl;
    }
    expression->GetExpression()->Accept(this);
}

void CCheckTypesVisitor::Visit(CLengthExpression *expression) {
    if(expression->getType() != INT_ARRAY_TYPE) {
        std::cout << "try use length to " << expression->getType() << endl;
    }
    expression->getExpression()->Accept(this);
}

void CCheckTypesVisitor::Visit(CArrayConstructionExpression *expression) {
    if(expression->getSize()->getType() != INT_TYPE) {
        std::cout << "try to create array with not int size " << expression->getType() << endl;
    }
    expression->getSize()->Accept(this);

}


void CCheckTypesVisitor::Visit(CConstructClassExpression *expression) {
    if(classes.find(expression->getType()) == classes.end()){
        std::cout << "create not exist class " << expression->getType() << endl;
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
    if(statement->GetExpression()->getType() != INT_TYPE) {
        std::cout << "print from not int " << statement->GetExpression()->getType() << endl;
    }
}

void CCheckTypesVisitor::Visit(CIfElseStatement *statement) {
    statement->getExpression()->Accept(this);
    statement->getIfStatement()->Accept(this);
    statement->getElseStatement()->Accept(this);
    if(statement->getExpression()->getType() != BOOLEAN_TYPE) {
        std::cout << "not boolean condition in if " << statement->getExpression()->getType() << endl;
    }
}


void CCheckTypesVisitor::Visit(CWhileStatement *statement) {
    statement->getCondition()->Accept(this);
    statement->getBody()->Accept(this);
    if(statement->getCondition()->getType() != BOOLEAN_TYPE) {
        std::cout << "not boolean condition in while " << statement->getCondition()->getType() << endl;
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
        //Проблема параметров функции или объявления переменых внутри метода
        if (inMethodBody) {
            std::cout << "Non existing type in variable declaration " <<
                      typeName << "in class " << currentClass << endl;
        } else {
            std::cout << "Non existing type in function param list " <<
                      currentClass << "::" << currentMethod << "::" << typeName << endl;
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
        std::cout << "Non existing return type " << typeName << " in method  "
                  << currentClass << "::" << currentMethod << endl;
    }
    inMethodBody = false;
    currentMethod = "";
}


void CCheckTypesVisitor::Visit(CMethodCallExpression *exp) {
    //по сути имя класса вызывающего метод
    exp->setType(NONE_TYPE);
    std::string className = exp->getObject()->getType();
    if(classes.find(className) == classes.end()){
        std::cout << "Wrong class for method call expression " << className << "::"
                  << exp->getMethodId()->GetName() << endl;
    } else {
        for(auto method : classes[className].methodsDeclarations) {
            if(method.name == exp->getMethodId()->GetName()) {
                if(method.visibility == "private" && className != currentClass) {
                    std::cout << "try to call private method" << className << "::" <<
                              method.name << " from class" << currentClass << endl;
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

