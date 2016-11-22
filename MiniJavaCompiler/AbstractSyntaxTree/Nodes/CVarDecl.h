//
// Created by nismohl on 01.11.16.
//

#pragma once

#include <Nodes/IStatement.h>

class CVarDecl : public IStatement {
public:
    CVarDecl(const Location location,
             const std::string typeNameArg,
             const std::string variableNameArg);

    std::string GetTypeName() const;
    std::string GetVariableName() const;
    int getTypeNameId() { return typeNameId; }
    int getVariableNameId() { return variableNameId; }

    void Accept(IVisitor*);

private:
    int typeNameId;
    int variableNameId;
};
