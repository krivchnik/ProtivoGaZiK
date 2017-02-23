//
// Created by nismohl on 23.02.17.
//

#include <Visitors/CSymbolTable.h>


std::vector<MethodInfo> CSymbolTable::GetAvailableMethodsInfo(std::string className) {
    if (className == "") {
        return std::vector<MethodInfo>();
    }

    std::vector<MethodInfo> availMethods(classes[className].methodsDeclarations);

    std::vector<std::string> baseClasses = GetAllBaseClasses(className);
    for (auto it = baseClasses.begin(); it != baseClasses.end(); ++it) {
        std::vector<MethodInfo> publicMethods = classes[*it].getPublicMethodsInfo();
        availMethods.insert(availMethods.end(), publicMethods.begin(), publicMethods.end());
    }

    return availMethods;
}

std::vector<std::string> CSymbolTable::GetAllBaseClasses(std::string className) {

    std::vector<std::string> visitedClasses;
    if (classes.find(className) == classes.end()) {
        return visitedClasses;
    }

    ClassInfo classInfo = classes[className];

    ClassInfo currentClass = classInfo;
    while(currentClass.HasBase()) {
        auto currentClassIt = classes.find(currentClass.baseId);
        if (currentClassIt == classes.end()) {
            break;
        }

        currentClass = currentClassIt->second;

        for (auto it = visitedClasses.begin(); it != visitedClasses.end(); ++it) {
            if (*it == currentClass.name) {
                break;
            }
        }

        visitedClasses.push_back(currentClass.name);
    }
    return visitedClasses;
}

ClassInfo CSymbolTable::GetClassInfo(std::string className) {
    if (classes.find(className) != classes.end()) {
        return classes[className];
    } else {
        ClassInfo notFoundClass;
        notFoundClass.name = "";
        return notFoundClass;
    }
}
