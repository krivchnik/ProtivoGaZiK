#pragma once

#include <Nodes/INode.h>

class IExpression: public INode {
public:
	virtual void Accept(IVisitor*) = 0;
};