#include <Visitors/CPrintVisitor.h>

#include <Nodes/CAssignStatement.h>
#include <Nodes/CAssignItemStatement.h>
#include <Nodes/CCompoundStatement.h>
#include <Nodes/CPrintStatement.h>
#include <Nodes/CIfElseStatement.h>
#include <Nodes/CWhileStatement.h>

#include <Nodes/CIdExpression.h>
#include <Nodes/CBoolExpression.h>
#include <Nodes/CNumExpression.h>
#include <Nodes/CNotExpression.h>
#include <Nodes/COperationExpression.h>
#include <Nodes/CLengthExpression.h>

std::string GetOperationSign(int index) {
	std::vector<std::string> signs = {"addition", "subtraction", "multiplication", "mod", "and", "or", "less"};
	return signs[index];
}

void CPrintVisitor::StartVisit(INode* startNode, std::string filename) {

	expressionId = 0;

	file.open(filename);
	
	file << "digraph task1 {\n\t";

	startNode->Accept(this);

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

void CPrintVisitor::Visit(CBoolExpression* expression) {
	++expressionId;
	std::string newId = std::string("Bool") + std::to_string(expression->GetValue()) + delim + std::to_string(expressionId);
	file << newId;
	idsOfTokenWithBoxShape.push_back(newId);
}

void CPrintVisitor::Visit(CIdExpression* expression) {
	++expressionId;
	std::string newId = expression->GetName() + delim + std::to_string(expressionId);
	file << newId;
	idsOfTokenWithBoxShape.push_back(newId);
}

void CPrintVisitor::Visit(CNotExpression* expression) {
    ++expressionId;
    file << "not" << expressionId << getArrow();
    expression->GetExpression()->Accept(this);
}

void CPrintVisitor::Visit(CLengthExpression* expression) {
	++expressionId;
	expression->getExpression()->Accept(this);
	file << "getLength" + delim + std::to_string(expressionId);
	file << getEndLine();
}

void CPrintVisitor::Visit(CAssignStatement* statement) {
	int currentExpressionId = ++expressionId;
	file << "assignment" << delim << currentExpressionId << getArrow();
	statement->GetVariable()->Accept(this);
	file << getEndLine();
	file << "assignment" << delim << currentExpressionId << getArrow();
	statement->GetExpression()->Accept(this);
}


void CPrintVisitor::Visit(CAssignItemStatement* statement) {
    int currentExpressionId = ++expressionId;
    file << "assignmentItem" << delim << currentExpressionId << getArrow();
    statement->getId()->Accept(this);
    file << "[";
    statement->getExpressionInBrackets()->Accept(this);
    file << "]";
    file << getEndLine();
    file << "assignmentItem" << delim << currentExpressionId << getArrow();
    statement->getAssignedExpression()->Accept(this);
    file << getEndLine();
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


void CPrintVisitor::Visit(CIfElseStatement* statement) {
	int currentExpressionId = ++expressionId;
	file << "if" << delim << currentExpressionId << getArrow();
	statement->getExpression()->Accept(this);
	file << getEndLine();
    file << "if" << delim << currentExpressionId << getArrow();
    statement->getIfStatement()->Accept(this);
    file << getEndLine();
    file << "if" << delim << currentExpressionId << getArrow();
    statement->getElseStatement()->Accept(this);
}


void CPrintVisitor::Visit(CWhileStatement* statement) {
	int currentExpressionId = ++expressionId;
	file << "WhileCondition" << delim << currentExpressionId << getArrow();
	statement->getCondition()->Accept(this);
	file << getEndLine();
	file << "WhileBody" << delim << currentExpressionId << getArrow();
	statement->getBody()->Accept(this);
	file << getEndLine();

}

std::string CPrintVisitor::getArrow() const {
	return " -> ";
}

std::string CPrintVisitor::getEndLine() const {
	return ";\n\t";
}


