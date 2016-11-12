#pragma once

#include <Nodes/IExpression.h>
#include <vector>

class CListExpression : public IExpression {
public:
    void Add(std::shared_ptr<IExpression> exp);
    void Accept(IVisitor*);

    CListExpression(const std::string&);

    const std::vector<std::shared_ptr<IExpression>> &GetExpressions() const;

    const std::string &GetExpressionType() const;

private:
    std::vector<std::shared_ptr<IExpression> > expressions;
    std::string expressionType;
};
