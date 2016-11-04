#include <Visitors/CPrintVisitor.h>

#include <Nodes/CAssignStatement.h>
#include <Nodes/CAssignItemStatement.h>
#include <Nodes/CCompoundStatement.h>
#include <Nodes/CPrintStatement.h>
#include <Nodes/CIfElseStatement.h>
#include <Nodes/CWhileStatement.h>
#include <Nodes/CListStatement.h>

#include <Nodes/CVarDecl.h>
#include <Nodes/CListVarDecl.h>
#include <Nodes/CMethod.h>
#include <Nodes/CListMethodDecl.h>
#include <Nodes/CClass.h>
#include <Nodes/CMainClass.h>

#include <Nodes/CIdExpression.h>
#include <Nodes/CBoolExpression.h>
#include <Nodes/CNumExpression.h>
#include <Nodes/CNotExpression.h>
#include <Nodes/COperationExpression.h>
#include <Nodes/CLengthExpression.h>
#include <Nodes/CArrayConstructionExpression.h>
#include <Nodes/CConstructClassExpression.h>

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
	std::string newId = getNodeNameWithLabel(std::to_string(expression->GetNumber()), expressionId, "Number");
	file << newId;
    idsOfTokenWithBoxShape.push_back(newId);
}

void CPrintVisitor::Visit(CBoolExpression* expression) {
	++expressionId;
	std::string newId = getNodeNameWithLabel(std::to_string(expression->GetValue()), expressionId, "Bool");
	file << newId;
	idsOfTokenWithBoxShape.push_back(newId);
}

void CPrintVisitor::Visit(CIdExpression* expression) {
	++expressionId;
	std::string newId = getNodeNameWithLabel(expression->GetName(), expressionId, "");
	file << newId;
	idsOfTokenWithBoxShape.push_back(newId);
}

void CPrintVisitor::Visit(CNotExpression* expression) {
    ++expressionId;
    file << getNodeNameWithLabel("not", expressionId, "not") << getArrow();
    expression->GetExpression()->Accept(this);
}

void CPrintVisitor::Visit(CLengthExpression* expression) {
	++expressionId;
	expression->getExpression()->Accept(this);
	file << getArrow() << "getLength" + delim + std::to_string(expressionId);
}

void CPrintVisitor::Visit(CArrayConstructionExpression* expression) {
    ++expressionId;
    file << getNodeNameWithLabel("newIntArray", expressionId, "newIntArray") + getArrow() +
            getNodeNameWithLabel("withSize", expressionId, "withSize")  + getArrow();
    expression->getSize()->Accept(this);

}


void CPrintVisitor::Visit(CConstructClassExpression* expression) {
    ++expressionId;
    file << getNodeNameWithLabel("constructClass", expressionId, "constructClass") + getArrow() +
            getNodeNameWithLabel(expression->getClassID()->GetName(), expressionId, expression->getClassID()->GetName());
}

void CPrintVisitor::Visit(CAssignStatement* statement) {
	int currentExpressionId = ++expressionId;
    file << getNodeNameWithLabel("assignment", currentExpressionId, "assignment") << getArrow();
	statement->GetVariable()->Accept(this);
	file << getEndLine();
	file << getNodeNameWithLabel("assignment", currentExpressionId, "assignment") << getArrow();
	statement->GetExpression()->Accept(this);
}


void CPrintVisitor::Visit(CAssignItemStatement* statement) {
    int currentExpressionId = ++expressionId;
    file << getNodeNameWithLabel("assignmentItem", currentExpressionId, "assignmentItem") << getArrow();
    statement->getId()->Accept(this);
    file << "[";
    statement->getExpressionInBrackets()->Accept(this);
    file << "]";
    file << getEndLine();
    file << getNodeNameWithLabel("assignmentItem", currentExpressionId, "assignmentItem") << getArrow();
    statement->getAssignedExpression()->Accept(this);
}

void CPrintVisitor::Visit(CPrintStatement* statement) {
	++expressionId;
	file << getNodeNameWithLabel("println", expressionId, "println") <<  getArrow();
	statement->GetExpression()->Accept(this);
}

void CPrintVisitor::Visit(CCompoundStatement* statement) {
	int currentExpressionId = ++expressionId;
	file << getNodeNameWithLabel("compound", currentExpressionId, "compound") << getArrow();
	statement->GetLeftOperand()->Accept(this);
	file << getEndLine();
	file << getNodeNameWithLabel("compound", currentExpressionId, "compound") << getArrow();
	statement->GetRightOperand()->Accept(this);
}


void CPrintVisitor::Visit(CIfElseStatement* statement) {
	int currentExpressionId = ++expressionId;
	file << getNodeNameWithLabel("if", currentExpressionId, "if") << getArrow() <<
         getNodeNameWithLabel("condition", currentExpressionId, "condition") << getArrow();
	statement->getExpression()->Accept(this);
	file << getEndLine();
    file << getNodeNameWithLabel("if", currentExpressionId, "if") << getArrow() <<
         getNodeNameWithLabel("ifStatement", currentExpressionId, "ifStatement") << getArrow();
    statement->getIfStatement()->Accept(this);
    file << getEndLine();
    file << getNodeNameWithLabel("if", currentExpressionId, "if") << getArrow() <<
         getNodeNameWithLabel("elseStatement", currentExpressionId, "elseStatement") << getArrow();
    statement->getElseStatement()->Accept(this);
}


void CPrintVisitor::Visit(CWhileStatement* statement) {
	int currentExpressionId = ++expressionId;
	file << getNodeNameWithLabel("While", currentExpressionId, "While") << currentExpressionId << getArrow() <<
         getNodeNameWithLabel("condition", currentExpressionId, "condition") << getArrow();
	statement->getCondition()->Accept(this);
	file << getEndLine();
	file << getNodeNameWithLabel("While", currentExpressionId, "While") << getArrow() <<
         getNodeNameWithLabel("While", currentExpressionId, "While") << getArrow();
	statement->getBody()->Accept(this);
}

void CPrintVisitor::Visit(CListStatement* statement) {
    int currentExpressionId = ++expressionId;

    auto statements = statement->GetStatements();
    size_t numberOfIterations = statements.size();

    for(size_t i = 0; i < numberOfIterations; ++i) {
        if (i != numberOfIterations - 1) {
            file << getNodeNameWithLabel("List" + statement->GetStatementType(), currentExpressionId, "List") << getArrow();
            statements[i]->Accept(this);
            file << getEndLine();
        } else {
            file << getNodeNameWithLabel("List" + statement->GetStatementType(), currentExpressionId, "List") << getArrow();
            statements[numberOfIterations - 1]->Accept(this);
        }
    }
    if (numberOfIterations == 0) {
        file << getNodeNameWithLabel("Empty", currentExpressionId, "Empty");
    }
}

void CPrintVisitor::Visit(CVarDecl* decl) {
    int currentExpressionId = ++expressionId;
    file << "VariableDeclaration" << delim << currentExpressionId << getArrow();
    file << decl->GetTypeName() << delim << ++expressionId << getEndLine();
    file << "VariableDeclaration" << delim << currentExpressionId << getArrow();
    file << decl->GetVariableName() << delim << ++expressionId;
}

void CPrintVisitor::Visit(CListVarDecl* declarationList) {
    int currentExpressionId = ++expressionId;

    auto declarations = declarationList->GetDeclarations();
    size_t numberOfIterations = declarations.size();

    for(size_t i = 0; i < numberOfIterations; ++i) {
        if (i != numberOfIterations - 1) {
            file << "ListVar" << delim << currentExpressionId << getArrow();
            declarations[i]->Accept(this);
            file << getEndLine();
        } else {
            file << "ListVar" << delim << currentExpressionId << getArrow();
            declarations[numberOfIterations - 1]->Accept(this);
        }
    }
    if (numberOfIterations == 0) {
        file << "Empty" << delim << currentExpressionId;
    }
}


void CPrintVisitor::Visit( CMethod* statement ) {
    int currentExpressionId = ++expressionId;
    file << "CMethod" << delim << currentExpressionId << getArrow() << "Visibility" << currentExpressionId << getArrow();
    file << statement->getVisibility();
    file << getEndLine();

    file << "CMethod" << delim << currentExpressionId << getArrow() << "TypeName" << currentExpressionId << getArrow();
    file << statement->getTypeName();
    file << getEndLine();

    file << "CMethod" << delim << currentExpressionId << getArrow() << "ID" << currentExpressionId << getArrow();
    statement->getId()->Accept(this);
    file << getEndLine();

    file << "CMethod" << delim << currentExpressionId << getArrow() << "Params" << currentExpressionId << getArrow();
    statement->getParameters()->Accept(this);
    file << getEndLine();

    file << "CMethod" << delim << currentExpressionId << getArrow() << "VariablesDeclarations" << currentExpressionId << getArrow();
    statement->getListDeclarations()->Accept(this);
    file << getEndLine();

    file << "CMethod" << delim << currentExpressionId << getArrow() << "ListStatementsInMethod" << currentExpressionId << getArrow();
    statement->getListStatements()->Accept(this);
    file << getEndLine();

    file << "CMethod" << delim << currentExpressionId << getArrow() << "ReturnExpression" << currentExpressionId << getArrow();
    statement->getReturnExpression()->Accept(this);
}

void CPrintVisitor::Visit(CListMethodDecl* declarationList) {
    int currentExpressionId = ++expressionId;

    auto declarations = declarationList->GetDeclarations();
    size_t numberOfIterations = declarations.size();

    for(size_t i = 0; i < numberOfIterations; ++i) {
        if (i != numberOfIterations - 1) {
            file << "ListMethods" << delim << currentExpressionId << getArrow();
            declarations[i]->Accept(this);
            file << getEndLine();
        } else {
            file << "ListMethods" << delim << currentExpressionId << getArrow();
            declarations[numberOfIterations - 1]->Accept(this);
        }
    }
    if (numberOfIterations == 0) {
        file << "Empty" << delim << currentExpressionId;
    }
}

void CPrintVisitor::Visit( CClass* statement ) {
    int currentExpressionId = ++expressionId;

    file << "CClass" << delim << currentExpressionId << getArrow() << "ID" << currentExpressionId << getArrow();
    statement->getId()->Accept(this);
    file << getEndLine();

    if (statement->getBaseId().get() != nullptr) {
        file << "CClass" << delim << currentExpressionId << getArrow() << "BaseID" << currentExpressionId << getArrow();
        statement->getBaseId()->Accept(this);
        file << getEndLine();
    }

    file << "CClass" << delim << currentExpressionId << getArrow() << "Fields" << currentExpressionId << getArrow();
    statement->getFields()->Accept(this);
    file << getEndLine();

    file << "CClass" << delim << currentExpressionId << getArrow() << "Methods" << currentExpressionId << getArrow();
    statement->getMethods()->Accept(this);
}


void CPrintVisitor::Visit( CMainClass* statement ) {
    int currentExpressionId = ++expressionId;

    file << "CMainClass" << delim << currentExpressionId << getArrow() << "ID" << currentExpressionId << getArrow();
    statement->GetClassId()->Accept(this);
    file << getEndLine();

    file << "CMainClass" << delim << currentExpressionId << getArrow() << "ArgID" << currentExpressionId << getArrow();
    statement->GetArgId()->Accept(this);
    file << getEndLine();

    file << "CMainClass" << delim << currentExpressionId << getArrow() << "Statement" << currentExpressionId << getArrow();
    statement->GetStatement()->Accept(this);
}




std::string CPrintVisitor::getArrow() const {
	return " -> ";
}

std::string CPrintVisitor::getEndLine() const {
	return ";\n\t";
}

std::string CPrintVisitor::getNodeNameWithLabel(std::string label, int id, std::string nodeName ) const {
    return "{" + nodeName + label + delim +
           std::to_string(id) +"[label=\"" + label + "\"]" +  "}";
}






