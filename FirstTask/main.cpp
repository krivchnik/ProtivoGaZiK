#include <iostream>
#include <memory>


class IVistor {
	virtual void visit(COperandExpression*) = 0;
	virtual void visit(CNumExpression*) = 0;
	virtual void visit(CIdExpression*) = 0;
	virtual void visit(CAssignStatement*) = 0;
};

class CPrintVisitor: public IVistor {

	void visit(COperandExpression* exp) {
		exp->leftOperand->Accept(this);
		std::cout << exp->type << "\n";
		exp->rightOperand->Accept(this);
	}

	void visit(CNumExpression* exp) {
		std::cout << exp->number << "\n";
	}

	void visit(CAssignStatement* st) {
		st->leftOperand->Accept(this);
		std::cout << "Assign statement";
		st->rightOperand->Accept(this);\
	}
};

int main() {

	/*make tree*/


	return 0;
}
