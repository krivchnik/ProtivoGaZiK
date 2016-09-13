#include "CPrintVisitor.h"


void CPrintVisitor::StartVisit(INode* startNode, std::string filename) {
	file.open(filename);
	
	file << "digraph task1 {\n";

	startNode->Accept(this);

	file << "\n}";
	file.close();	
}

void CPrintVisitor::visit(COperationExpression* expression) {
	file << expression->GetType() << "->";
	exp->leftOperand->Accept(this);
	file << ";\n" << expression->GetType() << "->"
	exp->rightOperand->Accept(this);
}

void CPrintVisitor::visit(CNumExpression* expression) {
	file << expression->GetNumber();
}

void CPrintVisitor::visit(CIdExpression* expression) {
	file << expression->GetName();
}

void CPrintVisitor::visit(CAssignStatement* statement) {
	file << " = " << "->";
	exp->leftOperand->Accept(this);
	file << ";\n" << " = " << "->"
	exp->rightOperand->Accept(this);
}

void CPrintVisitor::visit(CCompoundStatement* statement) {
	file << " compound " << "->";
	statement->leftOperand->Accept(this);
	file << ";\n compound " << "->";
	statement->rightOperand->Accept(this);
}