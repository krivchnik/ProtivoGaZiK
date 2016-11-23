#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <Nodes/INode.h>
#include <set>
#include <map>


struct VariableInfo{
    Location location;
    std::string type;
    std::string name;

    friend std::ostream& operator <<(std::ostream &stream, const VariableInfo &varInfo);
};

struct MethodInfo{
    Location location;
    std::string returnedType;
    std::string name;
    std::vector<VariableInfo> paramList;
    std::vector<VariableInfo> variablesList;
    std::string visibility;

    friend std::ostream& operator <<(std::ostream &stream, const MethodInfo &methodInfo);
};

struct ClassInfo {
    Location location;
    std::vector<MethodInfo> methodsDeclarations;
    std::vector<VariableInfo> variableDeclaration;
    std::string baseId;
    std::string name;

    friend std::ostream& operator <<(std::ostream &stream, const ClassInfo &classInfo);

    std::set<std::string> getPublicMethods();
    std::vector<MethodInfo> getPublicMethodsInfo();
    bool HasBase();
};



