#pragma once

#include "IVisitor.h"
#include "INode.h"

#include <fstream>

class CPrintVisitor: public IVisitor {
public:
	void StartVisit(INode* startNode, std::string filename);

	void Visit(CCompoundStatement*);
	void Visit(CAssignStatement*);
	void Visit(CPrintStatement*);

	void Visit(COperationExpression*);
	void Visit(CNumExpression*);
	void Visit(CIdExpression*);

private:

	int count_;

	std::string delim = "AAA";

	std::ofstream file;

	std::string getArrow();
	std::string getEndLine();
};
