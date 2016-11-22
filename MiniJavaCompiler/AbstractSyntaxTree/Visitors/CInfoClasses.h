#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <Nodes/INode.h>
#include <set>
#include <map>


struct VariableInfo{
    Location location;
    int typeId;
    int nameId;
    void Print(std::ostream& stream);
};

struct MethodInfo{
    Location location;
    int returnedTypeId;
    int nameId;
    std::vector<VariableInfo> paramList;
    std::vector<VariableInfo> variablesList;
    bool isPublic;
    void Print(std::ostream& stream);
};

struct ClassInfo {
    Location location;
    std::vector<MethodInfo> methodsDeclarations;
    std::vector<VariableInfo> variableDeclaration;
    int baseId;
    int nameId;

    void Print(std::ostream &stream);
    std::set<int> getPublicMethods();
    std::vector<MethodInfo> getPublicMethodsInfo();
    bool HasBase();
};



