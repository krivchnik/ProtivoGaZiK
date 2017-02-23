//
// Created by nismohl on 23.02.17.
//
#pragma once

#include <Visitors/CInfoClasses.h>

class CSymbolTable {
public:
    CSymbolTable(const std::map<std::string, ClassInfo >& classes)
            : classes(classes) {}

    std::vector<MethodInfo> getAvailableMethodsInfo(const std::string& currentClass) const;

    //все классы-родители переданного класса
    std::vector<std::string> getAllBaseClasses(std::string className);

private:
    std::map<std::string, ClassInfo > classes;
};
