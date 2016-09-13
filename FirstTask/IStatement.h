#pragma once

#include "INode.h"

class IStatement: public INode {
public:
	virtual void Accept(IVisitor*) = 0;
};