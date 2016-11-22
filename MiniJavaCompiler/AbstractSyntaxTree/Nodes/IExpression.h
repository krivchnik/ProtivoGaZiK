#pragma once

#include <Nodes/INode.h>

const int INT_TYPE = strings.add("int");
const int INT_ARRAY_TYPE = strings.add("intArray");
const int BOOLEAN_TYPE = strings.add("boolean");
const int NONE_TYPE = strings.add("none");

class IExpression: public INode {
public:
	virtual void Accept(IVisitor*) = 0;

	const std::string &GetType() const {
		return strings.get(typeId);
	}

	void SetType(const std::string &type) {
		typeId = strings.add(type);
	}

	int getTypeId() { return typeId; }

protected:
	int typeId;
};