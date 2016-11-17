#pragma once

#include <Nodes/IExpression.h>

class CLengthExpression : public IExpression {
public:
    CLengthExpression(const Location location, std::shared_ptr <IExpression> expression);

    std::shared_ptr <IExpression> getExpression();

    void Accept(IVisitor* );


private:
    std::shared_ptr<IExpression> expression;
};

