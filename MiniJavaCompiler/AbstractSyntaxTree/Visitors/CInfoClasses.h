#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <Nodes/INode.h>

struct VariableInfo{
    Location location;
    std::string type;
    std::string name;
    void Print(std::ostream& stream);
};

struct MethodInfo{
    Location location;
    std::string returnedType;
    std::string name;
    std::vector<VariableInfo> paramList;
    std::vector<VariableInfo> variablesList;
    std::string visibility;
    void Print(std::ostream& stream);
};

struct ClassInfo {
    Location location;
    std::vector<MethodInfo> methodsDeclarations;
    std::vector<VariableInfo> variableDeclaration;
    std::string baseId;
    std::string name;

    void Print(std::ostream &stream);

    bool HasBase();
};

