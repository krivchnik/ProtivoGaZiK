//
// Created by kagudkov on 12.11.16.
//

#include <Analyzer/CAnalyzer.h>


void CAnalyzer::analyze() {
    checkCycleInheritance();
    checkMethodOverrides();
    checkTypes();
}

CAnalyzer::CAnalyzer(std::shared_ptr<CProgram> program) : program(program) {
    CGetClassesVisitor getClassesVisitor;
    getClassesVisitor.Visit(program.get());
    classes = getClassesVisitor.getClasses();
    for (auto it = classes.begin(); it != classes.end(); ++it) {
        it->second.Print(std::cout);
    }
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
            nextBaseName = classes[nextBaseName].baseId;
            nameOfClassedInChain.push_back(nextBaseName);
            if (used[nextBaseName]) {
                std::cout << "Recursive inheritance " << nameOfClassedInChain[0];
                for (size_t i = 1; i < nameOfClassedInChain.size(); ++i) {
                    std::cout << " -> " << nameOfClassedInChain[i];
                }
                break;
            }
            used[nextBaseName] = true;
        }
        for (auto iter = classes.begin(); iter != classes.end(); ++iter) {
            used[iter->first] = false;
        }
    }

}

std::set<std::string> CAnalyzer::checkTypes() {

    CCheckTypesVisitor checkTypesVisitor(classes);
    checkTypesVisitor.Visit(program.get());
    return std::set<std::string>();
}

std::set<std::string> getPublicMethods(ClassInfo classInfo) {
    std::set<std::string> publicMethods;
    for (int i = 0; i < classInfo.methodsDeclarations.size(); ++i) {
        if (classInfo.methodsDeclarations[i].visibility == "public") {
            publicMethods.insert(classInfo.methodsDeclarations[i].name);
        }
    }
    return publicMethods;
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
        for (int i = 0; i < it->second.methodsDeclarations.size(); ++i) {
            if(methods.find(it->second.methodsDeclarations[i].name) != methods.end()) {
                std::cout << "redefinition of method " << it->second.methodsDeclarations[i].name
                          << " in class " << it->first << endl;
            }
            methods.insert(it->second.methodsDeclarations[i].name);
        }

        //проверка того, что метода не было в предке
        used[it->first] = true;
        std::vector<std::string> nameOfClassedInChain;
        std::vector<std::set<std::string> > nameOfPublicMethods;
        std::string nextBaseName = it->first;
        nameOfClassedInChain.push_back(nextBaseName);
        nameOfPublicMethods.push_back(getPublicMethods(it->second));
        while (classes[nextBaseName].HasBase() && !used[classes[nextBaseName].baseId]) {
            nextBaseName = classes[nextBaseName].baseId;
            nameOfClassedInChain.push_back(nextBaseName);
            nameOfPublicMethods.push_back(getPublicMethods(classes[nextBaseName]));
            used[nextBaseName] = true;
        }
        for (int j = 0; j < classes[it->first].methodsDeclarations.size(); ++j) {
            std::string methodName = classes[it->first].methodsDeclarations[j].name;
            for (int k = 1; k < nameOfClassedInChain.size(); ++k) {
                if(nameOfPublicMethods[k].find(methodName) != nameOfPublicMethods[k].end()) {
                    std::cout << "Override method " << nameOfClassedInChain[k] << "::" << methodName <<
                              " in class " << it->first << endl;
                }
            }
        }
        //те классы которые мы уже видели
        for (auto iter = classes.begin(); iter != classes.end(); ++iter) {
            used[iter->first] = false;
        }

    }

}

