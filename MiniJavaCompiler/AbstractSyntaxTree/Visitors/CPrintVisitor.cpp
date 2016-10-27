#include <Visitors/CPrintVisitor.h>

#include <Nodes/CAssignStatement.h>
#include <Nodes/CCompoundStatement.h>
#include <Nodes/CPrintStatement.h>
#include <Nodes/CIfElseStatement.h>
#include <Nodes/CWhileStatement.h>

#include <Nodes/CIdExpression.h>
#include <Nodes/CNumExpression.h>
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
	file << "ifExpression" << delim << currentExpressionId << getArrow();
	statement->getExpression()->Accept(this);
	file << getEndLine();
    file << "ifStatement" << delim << currentExpressionId << getArrow();
    statement->getIfStatement()->Accept(this);
    file << getEndLine();
    file << "elseStatement" << delim << currentExpressionId << getArrow();
    statement->getElseStatement()->Accept(this);
    file << getEndLine();
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


