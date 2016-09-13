#pragma once

#include "IVisitor.h"

#include <fstream>

class CPrintVisitor: public IVisitor {
public:
	void StartVisit(INode* startNode, std::string filename);

private:
	std::ofstream file;
};
