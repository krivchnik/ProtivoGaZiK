//
// Created by nismohl on 01.11.16.
//

#pragma once

#include <Nodes/IStatement.h>

class CVarDecl : public IStatement {
public:
    CVarDecl(const std::string typeNameArg , const std::string variableNameArg);
    std::string GetTypeName() const;
    std::string GetVariableName() const;

    void Accept(IVisitor*);

private:
    std::string typeName;
    std::string variableName;
};
