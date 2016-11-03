#pragma once


#include <Nodes/IStatement.h>
#include <vector>

class CListMethod : public IStatement {
public:
    void Add(std::shared_ptr<IStatement> statement);
    void Accept(IVisitor*);

    CListMethod();

    const std::vector<std::shared_ptr<IStatement>> &GetMethods() const;


private:
    std::vector<std::shared_ptr<IStatement> > methods;

};


