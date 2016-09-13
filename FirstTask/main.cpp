#include "CNumExpression.h"
#include "COperationExpression.h"
#include "CIdExpression.h"

#include "CCompoundStatement.h"
#include "CAssignStatement.h"

int main() {

	std::shared_ptr<CNumExpression> five(new CNumExpression(5));
	std::shared_ptr<CNumExpression> three(new CNumExpression(3));
	std::shared_ptr<COperationExpression> addition(five, three, new CNumExpression(OperationType::addition));
	std::shared_ptr<CIdExpression> a_variable(std::string("a"));
	std::shared_ptr<CAssignStatement> assign(a_variable, addition);

	CPrintVisitor visitor;
	visitor(assign);
	return 0;
}
