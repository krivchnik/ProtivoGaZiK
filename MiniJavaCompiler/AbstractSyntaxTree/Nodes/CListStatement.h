#pragma once

#include <Nodes/IStatement.h>
#include <vector>

class CListStatement : public IStatement {
public:
    void Add(std::shared_ptr<IStatement> statement);
    void Accept(IVisitor*);

    CListStatement();

    const std::vector<std::shared_ptr<IStatement>> &GetStatements() const;

private:
    std::vector<std::shared_ptr<IStatement> > statements;
};
