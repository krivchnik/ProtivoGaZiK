//
// Created by nismohl on 01.11.16.
//

#include <Nodes/CVarDecl.h>

CVarDecl::CVarDecl(const Location location,
                   const std::string typeName,
                   const std::string variableName)
        : typeName(typeName),
          variableName(variableName) {

    this->location = location;
}

std::string CVarDecl::GetTypeName() const {
    return typeName;
}

std::string CVarDecl::GetVariableName() const {
    return variableName;
}

void CVarDecl::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}


