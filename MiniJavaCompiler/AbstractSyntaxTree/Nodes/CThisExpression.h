//
// Created by nismohl on 12.11.16.
//
#pragma once

#include <Nodes/IExpression.h>

class CThisExpression: public IExpression {
public:
    CThisExpression(const Location location);
    void Accept(IVisitor*);
};