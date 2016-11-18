#pragma once

#include <Nodes/INode.h>

const std::string INT_TYPE = "int";
const std::string INT_ARRAY_TYPE = "intArray";
const std::string BOOLEAN_TYPE = "boolean";
const std::string NONE_TYPE = "none";

class IExpression: public INode {
public:
	virtual void Accept(IVisitor*) = 0;

protected:
public:
	const std::string &getType() const {
		return type;
	}

	void setType(const std::string &type) {
		IExpression::type = type;
	}

protected:
	std::string type;
};