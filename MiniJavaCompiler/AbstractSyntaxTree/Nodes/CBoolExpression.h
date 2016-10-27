#pragma once

#include <Nodes/IExpression.h>

class CBoolExpression: public IExpression {
public:
    CBoolExpression(bool value);
    bool GetValue();

    void Accept(IVisitor*);
private:
    bool value;
};
