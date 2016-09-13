#pragma once

#include "IVisitor.h"

#include <memory>

class INode {
public:
	virtual void Accept(IVisitor*) = 0;
};