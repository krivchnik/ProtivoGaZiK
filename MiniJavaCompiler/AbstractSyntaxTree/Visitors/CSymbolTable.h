//
// Created by nismohl on 23.02.17.
//
#pragma once

#include <Visitors/CInfoClasses.h>

class CSymbolTable {
public:
    CSymbolTable(const std::map<std::string, ClassInfo >& classes)
            : classes(classes) {}

    std::vector<MethodInfo> GetAvailableMethodsInfo(std::string currentClass);

    //все классы-родители переданного класса
    std::vector<std::string> GetAllBaseClasses(std::string className);

    ClassInfo GetClassInfo(std::string className) {
        if (classes.find(className) != classes.end()) {
            return classes[className];
        } else {
            ClassInfo notFoundClass;
            notFoundClass.name = "";
            return notFoundClass;
        }
    }

private:
    std::map<std::string, ClassInfo > classes;
};
