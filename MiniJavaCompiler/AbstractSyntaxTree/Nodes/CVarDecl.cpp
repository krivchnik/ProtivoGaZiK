//
// Created by nismohl on 01.11.16.
//

#include <Nodes/CVarDecl.h>

CVarDecl::CVarDecl(const std::string typeNameArg, const std::string variableNameArg)
        : typeName(typeNameArg), variableName(variableNameArg)
{}

std::string CVarDecl::GetTypeName() const {
    return typeName;
}

std::string CVarDecl::GetVariableName() const {
    return variableName;
}

void CVarDecl::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}


