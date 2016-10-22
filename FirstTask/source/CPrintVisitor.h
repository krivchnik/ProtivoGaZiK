#pragma once

#include "IVisitor.h"
#include "INode.h"
#include <vector>

#include <fstream>

class CPrintVisitor: public IVisitor {
public:
	void StartVisit(INode* startNode, std::string filename);

	void Visit(CAssignStatement*);
	void Visit(CCompoundStatement*);
	void Visit(CPrintStatement*);

	void Visit(CIdExpression*);
	void Visit(CNumExpression*);
	void Visit(COperationExpression*);

private:

	int expressionId;
    std::vector<std::string> idsOfTokenWithBoxShape;
	std::string delim = "A";

	std::ofstream file;

	std::string getArrow();
	std::string getEndLine();
};
