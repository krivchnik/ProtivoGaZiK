//
// Created by nismohl on 12.11.16.
//

#pragma once

#include <Nodes/IStatement.h>
#include <Nodes/IExpression.h>

class CGetItemExpression : public IExpression {
public:
    CGetItemExpression(const std::shared_ptr<IExpression> &object, const std::shared_ptr<IExpression> &index);
    const std::shared_ptr<IExpression> &GetObject() const;
    const std::shared_ptr<IExpression> &GetIndex() const;
    void Accept(IVisitor*);

private:
    std::shared_ptr<IExpression> object;
    std::shared_ptr<IExpression> index;
};


