#include "CPrintVisitor.h"

#include "CCompoundStatement.h"
#include "CAssignStatement.h"
#include "COperationExpression.h"
#include "CNumExpression.h"
#include "CIdExpression.h"

#include <vector>

std::string GetOperationSign(int index) {
	std::vector<std::string> signs = {"addition", "subtraction", "multiplication", "mod", "and", "or", "less"};
	return signs[index];
}

void CPrintVisitor::StartVisit(INode* startNode, std::string filename) {

	count_ = 0;

	file.open(filename);
	
	file << "digraph task1 {\n\t";

	startNode->Accept(this);

	file << "\n}";
	file.close();	
}

void CPrintVisitor::Visit(COperationExpression* expression) {

	int cur_count = ++count_;

	file << GetOperationSign(expression->GetOperationType()) << delim << cur_count << getArrow();
	expression->GetLeftOperand()->Accept(this);
	file << getEndLine() << GetOperationSign(expression->GetOperationType()) << delim << cur_count << getArrow();
	expression->GetRightOperand()->Accept(this);
}

void CPrintVisitor::Visit(CNumExpression* expression) {
	file << "Number" << expression->GetNumber() << delim << ++count_;
}

void CPrintVisitor::Visit(CIdExpression* expression) {
	file << expression->GetName() << delim << ++count_;
}

void CPrintVisitor::Visit(CAssignStatement* statement) {
	file << "assignment" << getArrow();
	statement->GetVariable()->Accept(this);
	file << getEndLine() << "assignment" << getArrow();
	statement->GetExpression()->Accept(this);
}

void CPrintVisitor::Visit(CCompoundStatement* statement) {
	file << "compound" << getArrow();
	statement->GetLeftOperand()->Accept(this);
	file << getEndLine() << "compound" << getArrow();
	statement->GetRightOperand()->Accept(this);
}

std::string CPrintVisitor::getArrow() {
	return " -> ";
}

std::string CPrintVisitor::getEndLine() {
	return ";\n\t";
}