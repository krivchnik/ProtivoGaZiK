#pragma once

#include <Nodes/IExpression.h>

class CBoolExpression: public IExpression {
public:
    CBoolExpression(const Location location, bool value);
    bool GetValue();

    void Accept(IVisitor*);
private:
    bool value;
};
