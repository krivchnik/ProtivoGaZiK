#pragma once

#include <Nodes/INode.h>

class IStatement: public INode {
public:
	virtual void Accept(IVisitor*) = 0;
};