#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <Nodes/INode.h>
#include <set>
#include <map>
#include <Nodes/IExpression.h>


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

    VariableInfo GetVariableOrParamInfo(const std::string& name) const {
        for (auto it = paramList.begin(); it != paramList.end(); ++it) {
            if (it->name == name) {
                return *it;
            }
        }
        for (auto it = variablesList.begin(); it != variablesList.end(); ++it) {
            if (it->name == name) {
                return *it;
            }
        }
        VariableInfo notFoundValue;
        notFoundValue.type = NONE_TYPE;
        return notFoundValue;
    }

    friend std::ostream& operator <<(std::ostream &stream, const MethodInfo &methodInfo);
};

struct ClassInfo {
    Location location;
    std::vector<MethodInfo> methodsDeclarations;
    std::vector<VariableInfo> variableDeclaration;
    std::string baseId;
    std::string name;

    friend std::ostream& operator <<(std::ostream &stream, const ClassInfo &classInfo);

    MethodInfo GetMethodInfo(const std::string& name) const {

        for (auto it = methodsDeclarations.begin(); it != methodsDeclarations.end(); ++it) {
            if (it->name == name) {
                return *it;
            }
        }
    }

    std::set<std::string> getPublicMethods();
    std::vector<MethodInfo> getPublicMethodsInfo();
    bool HasBase();
};



