//
// Created by nismohl on 01.11.16.
//

#include <Nodes/CVarDecl.h>

CVarDecl::CVarDecl(const Location location,
                   const std::string typeName,
                   const std::string variableName) {
    typeNameId = strings.add(typeName);
    variableNameId = strings.add(variableName);
    this->location = location;
}

std::string CVarDecl::GetTypeName() const {
    return strings.get(typeNameId);
}

std::string CVarDecl::GetVariableName() const {
    return strings.get(variableNameId);
}

void CVarDecl::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}


