#pragma once
#include <string>
#include <vector>
#include <iostream>

struct VariableInfo{
    std::string type;
    std::string name;
    void Print(std::ostream& stream);
};

struct MethodInfo{
    std::string returnedType;
    std::string name;
    std::vector<VariableInfo> paramList;
    std::vector<VariableInfo> variablesList;
    std::string visibility;
    void Print(std::ostream& stream);
};

struct ClassInfo {
    std::vector<MethodInfo> methodsDeclarations;
    std::vector<VariableInfo> variableDeclaration;
    std::string baseId;
    std::string name;

    void Print(std::ostream &stream);

    bool HasBase();
};

