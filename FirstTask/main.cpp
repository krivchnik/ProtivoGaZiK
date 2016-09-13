#include "CNumExpression.h"
#include "COperationExpression.h"
#include "CIdExpression.h"

#include "CCompoundStatement.h"
#include "CAssignStatement.h"
#include "CPrintVisitor.h"

int main() {

	std::shared_ptr<CNumExpression> five(new CNumExpression(5));
	std::shared_ptr<CNumExpression> three(new CNumExpression(3));
	std::shared_ptr<COperationExpression> addition(new COperationExpression(five, three, OperationType::addition));
	std::shared_ptr<CIdExpression> a_variable(new CIdExpression(std::string("a")));
	std::shared_ptr<CAssignStatement> assign(new CAssignStatement(a_variable, addition));

	CPrintVisitor visitor;
	visitor.StartVisit(assign.get(), std::string("../result.txt"));
	return 0;
}
