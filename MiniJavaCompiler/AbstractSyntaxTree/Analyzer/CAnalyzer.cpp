//
// Created by kagudkov on 12.11.16.
//

#include <Analyzer/CAnalyzer.h>

std::vector<ErrorDescription> CAnalyzer::analyze() {
    checkCycleInheritance();
    checkMethodOverrides();
    checkParamOverrides();
    checkTypes();
    return errors;
}

CAnalyzer::CAnalyzer(std::shared_ptr<CProgram> program) : program(program) {

    CGetClassesVisitor getClassesVisitor;
    getClassesVisitor.Visit(program.get());
    classes = getClassesVisitor.getClasses();
    auto classErrors = getClassesVisitor.GetErrors();
    errors.insert(errors.end(), classErrors.begin(), classErrors.end());
}

void CAnalyzer::checkCycleInheritance() {
    //те классы которые мы уже видели
    std::map<std::string, bool> used;
    for (auto it = classes.begin(); it != classes.end(); ++it) {
        used[it->first] = false;
    }
    for (auto it = classes.begin(); it != classes.end(); ++it) {
        used[it->first] = true;
        std::vector<std::string> nameOfClassedInChain;
        std::string nextBaseName = it->first;
        nameOfClassedInChain.push_back(nextBaseName);
        while (classes[nextBaseName].HasBase()) {
            ClassInfo nextBaseInfo = classes[nextBaseName];
            nextBaseName = nextBaseInfo.baseId;
            nameOfClassedInChain.push_back(nextBaseName);
            if (used[nextBaseName]) {
                std::string errorInfo = nameOfClassedInChain[0];
                for (size_t i = 1; i < nameOfClassedInChain.size(); ++i) {
                    errorInfo.append(" -> ").append(nameOfClassedInChain[i]);
                }
                errors.push_back({nextBaseInfo.location, ErrorType::RECURSIVE_INHERITANCE, errorInfo});
                break;
            }
            used[nextBaseName] = true;
        }
        for (auto iter = classes.begin(); iter != classes.end(); ++iter) {
            used[iter->first] = false;
        }
    }

}

void CAnalyzer::checkTypes() {

    CCheckTypesVisitor checkTypesVisitor(classes);
    checkTypesVisitor.Visit(program.get());
    auto typeErrors = checkTypesVisitor.GetErrors();
    errors.insert(errors.end(), typeErrors.begin(), typeErrors.end());
}

void CAnalyzer::checkMethodOverrides() {
    //те классы которые мы уже видели
    std::map<std::string, bool> used;
    for (auto it = classes.begin(); it != classes.end(); ++it) {
        used[it->first] = false;
    }

    for (auto it = classes.begin(); it != classes.end(); ++it) {

        //проверка внутри самого класса
        std::set<std::string> methods;
        for (unsigned int i = 0; i < it->second.methodsDeclarations.size(); ++i) {
            MethodInfo methodInfo = it->second.methodsDeclarations[i];
            if(methods.find(methodInfo.name) != methods.end()) {
                errors.push_back({methodInfo.location, ErrorType::REDEFINITION_METHOD, methodInfo.name});
            }
            methods.insert(methodInfo.name);
        }

        //проверка того, что метода не было в предке
        used[it->first] = true;
        std::vector<std::string> nameOfClassedInChain;
        std::vector<std::set<std::string> > nameOfPublicMethods;
        std::string nextBaseName = it->first;
        nameOfClassedInChain.push_back(nextBaseName);
        nameOfPublicMethods.push_back(classes[nextBaseName].getPublicMethods());
        while (classes[nextBaseName].HasBase() && !used[classes[nextBaseName].baseId]) {
            nextBaseName = classes[nextBaseName].baseId;
            nameOfClassedInChain.push_back(nextBaseName);
            nameOfPublicMethods.push_back(classes[nextBaseName].getPublicMethods());
            used[nextBaseName] = true;
        }
        for (unsigned int j = 0; j < classes[it->first].methodsDeclarations.size(); ++j) {
            MethodInfo methodInfo = classes[it->first].methodsDeclarations[j];
            for (unsigned int k = 1; k < nameOfClassedInChain.size(); ++k) {
                if(nameOfPublicMethods[k].find(methodInfo.name) != nameOfPublicMethods[k].end()) {
                    errors.push_back({methodInfo.location, ErrorType::REDEFINITION_METHOD, methodInfo.name});
                }
            }
        }
        //те классы которые мы уже видели
        for (auto iter = classes.begin(); iter != classes.end(); ++iter) {
            used[iter->first] = false;
        }
    }
}

//кажется, пока что не нужен поэтому недописан
std::vector<std::string> CAnalyzer::getAvailVariables(ClassInfo classInfo) {
    std::string nextClass = classInfo.name;
    std::vector<std::string> availBaseMethod;
    while(classes[nextClass].HasBase()){
        for(unsigned int i = 0; i < classes[nextClass].variableDeclaration.size(); ++i){
            availBaseMethod.push_back(classes[nextClass].variableDeclaration[i].name);
        }
        nextClass = classInfo.baseId;
    }
    return vector<string>();
}

void CAnalyzer::checkParamOverrides() {
    for(auto iter = classes.begin(); iter != classes.end(); ++iter) {
        ClassInfo classInfo = iter ->second;
        for(auto method : classInfo.methodsDeclarations){
            std::set<std::string> paramNames;
            for(auto varDecl : method.paramList) {
                if(paramNames.find(varDecl.name) != paramNames.end()) {
                    errors.push_back({varDecl.location, ErrorType::REDEFINITION_PARAM, varDecl.name});
                }
                paramNames.insert(varDecl.name);
            }
        }
    }
}
