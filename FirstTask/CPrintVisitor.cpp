#include "CPrintVisitor.h"

#include "CCompoundStatement.h"
#include "CAssignStatement.h"
#include "COperationExpression.h"
#include "CNumExpression.h"
#include "CIdExpression.h"

char GetOperationSign(int index) {
	std::string signs = "+-*/";
	return signs[index];
}

void CPrintVisitor::StartVisit(INode* startNode, std::string filename) {
	file.open(filename);
	
	file << "digraph task1 {\n\t";

	startNode->Accept(this);

	file << "\n}";
	file.close();	
}

void CPrintVisitor::Visit(COperationExpression* expression) {
	file << GetOperationSign(expression->GetOperationType()) << getArrow();
	expression->GetLeftOperand()->Accept(this);
	file << getEndLine() << GetOperationSign(expression->GetOperationType()) << getArrow();
	expression->GetRightOperand()->Accept(this);
}

void CPrintVisitor::Visit(CNumExpression* expression) {
	file << expression->GetNumber();
}

void CPrintVisitor::Visit(CIdExpression* expression) {
	file << expression->GetName();
}

void CPrintVisitor::Visit(CAssignStatement* statement) {
	file << "=" << getArrow();
	statement->GetVariable()->Accept(this);
	file << getEndLine() << "=" << getArrow();
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