//
// Created by nismohl on 03.11.16.
//

#pragma once

#include <Nodes/IStatement.h>
#include <Nodes/CMethod.h>

#include <vector>

class CListMethodDecl : public IStatement {
public:
    CListMethodDecl() {}

    void Add(std::shared_ptr<CMethod> statement);
    void Accept(IVisitor*);

    const std::vector<std::shared_ptr<CMethod>> &GetDeclarations() const;

private:
    std::vector<std::shared_ptr<CMethod> > declarations;
};