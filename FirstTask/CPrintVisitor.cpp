#include "CPrintVisitor.h"


void CPrintVisitor::StartVisit(INode* startNode, std::string filename) {
	file.open(filename);
	
	file << "digraph task1 {\n";

	startNode->Accept(this);

	file << "\n}";
	file.close();	
}

void CPrintVisitor::Visit(COperationExpression* expression) {
	file << expression->GetOperationType() << "->";
	expression->leftOperand->Accept(this);
	file << ";\n" << expression->GetOperationType() << "->";
	expression->rightOperand->Accept(this);
}

void CPrintVisitor::Visit(CNumExpression* expression) {
	file << expression->GetNumber();
}

void CPrintVisitor::Visit(CIdExpression* expression) {
	file << expression->GetName();
}

void CPrintVisitor::Visit(CAssignStatement* statement) {
	file << " = " << "->";
	expression->leftOperand->Accept(this);
	file << ";\n" << " = " << "->";
	expression->rightOperand->Accept(this);
}

void CPrintVisitor::Visit(CCompoundStatement* statement) {
	file << " compound " << "->";
	statement->leftOperand->Accept(this);
	file << ";\n compound " << "->";
	statement->rightOperand->Accept(this);
}