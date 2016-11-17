#pragma once

#include <Nodes/IExpression.h>

class CNotExpression: public IExpression {
public:
    CNotExpression(const Location location, std::shared_ptr<IExpression> exp);
    std::shared_ptr<IExpression> GetExpression();

    void Accept(IVisitor*);
private:
    std::shared_ptr<IExpression> expression;
};