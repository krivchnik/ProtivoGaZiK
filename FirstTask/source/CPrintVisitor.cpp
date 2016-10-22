#include "CPrintVisitor.h"

#include "CAssignStatement.h"
#include "CCompoundStatement.h"
#include "CPrintStatement.h"

#include "CIdExpression.h"
#include "CNumExpression.h"
#include "COperationExpression.h"

#include <vector>

std::string GetOperationSign(int index) {
	std::vector<std::string> signs = {"addition", "subtraction", "multiplication", "mod", "and", "or", "less"};
	return signs[index];
}

void CPrintVisitor::StartVisit(INode* startNode, std::string filename) {

	expressionId = 0;

	file.open(filename);
	
	file << "digraph task1 {\n\t";

	startNode->Accept(this);
    //распечатает id тех кто будет квадратным
    for(std::string name : idsOfTokenWithBoxShape){
    	file << getEndLine() << name << " [shape=box]";
    }
	file << ";\n}";
	file.close();	
}

void CPrintVisitor::Visit(COperationExpression* expression) {

	int currentExpressionId = ++expressionId;

	file << GetOperationSign(expression->GetOperationType()) << delim << currentExpressionId << getArrow();
	expression->GetLeftOperand()->Accept(this);
	file << getEndLine();
	file << GetOperationSign(expression->GetOperationType()) << delim << currentExpressionId << getArrow();
	expression->GetRightOperand()->Accept(this);
}

void CPrintVisitor::Visit(CNumExpression* expression) {
	++expressionId;
	std::string newId = std::string("Number") + std::to_string(expression->GetNumber()) + delim + std::to_string(expressionId);
	file << newId;
    idsOfTokenWithBoxShape.push_back(newId);
}

void CPrintVisitor::Visit(CIdExpression* expression) {
	++expressionId;
	std::string newId = expression->GetName() + delim + std::to_string(expressionId);
	file << newId;
	idsOfTokenWithBoxShape.push_back(newId);
}

void CPrintVisitor::Visit(CAssignStatement* statement) {
	int currentExpressionId = ++expressionId;
	file << "assignment" << delim << currentExpressionId << getArrow();
	statement->GetVariable()->Accept(this);
	file << getEndLine();
	file << "assignment" << delim << currentExpressionId << getArrow();
	statement->GetExpression()->Accept(this);
}

void CPrintVisitor::Visit(CPrintStatement* statement) {
	++expressionId;
	file << "println" << expressionId <<  getArrow();
	statement->GetExpression()->Accept(this);
	//file << getEndLine();
}

void CPrintVisitor::Visit(CCompoundStatement* statement) {
	int currentExpressionId = ++expressionId;
	file << "compound" << delim << currentExpressionId << getArrow();
	statement->GetLeftOperand()->Accept(this);
	file << getEndLine();
	file << "compound" << delim << currentExpressionId << getArrow();
	statement->GetRightOperand()->Accept(this);
}

std::string CPrintVisitor::getArrow() {
	return " -> ";
}

std::string CPrintVisitor::getEndLine() {
	return ";\n\t";
}