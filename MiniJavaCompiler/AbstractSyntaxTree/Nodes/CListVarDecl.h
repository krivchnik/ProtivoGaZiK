//
// Created by nismohl on 01.11.16.
//

// Deprecated since 04.11.16

#pragma once

#include <Nodes/IStatement.h>
#include <Nodes/CVarDecl.h>

#include <vector>

class CListVarDecl : public IStatement {
public:
    CListVarDecl() {}

    void Add(std::shared_ptr<CVarDecl> statement);
    void Accept(IVisitor*);

    const std::vector<std::shared_ptr<CVarDecl>> &GetDeclarations() const;

private:
    std::vector<std::shared_ptr<CVarDecl> > declarations;
};