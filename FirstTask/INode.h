#pragma once

#include "IVisitor.h"

class INode {
public:
	virtual void Accept(IVisitor*) = 0;
};