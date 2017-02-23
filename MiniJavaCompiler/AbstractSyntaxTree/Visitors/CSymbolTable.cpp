//
// Created by nismohl on 23.02.17.
//

#include <Visitors/CSymbolTable.h>


std::vector<MethodInfo> CSymbolTable::getAvailableMethodsInfo(std::string currentClass) {
    return std::vector<MethodInfo>();
}

std::vector<std::string> CSymbolTable::getAllBaseClasses(std::string className) {

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

        if (std::find(visitedClasses.begin(), visitedClasses.end(), currentClass.name) != visitedClasses.end()) {
            break;
        }

        visitedClasses.push_back(currentClass.name);
    }
    return visitedClasses;
}
