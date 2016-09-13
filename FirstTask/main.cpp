#include <iostream>

enum OperandType {
	'+', '-', '*', ':'
};

class INode {

};

class IExpression: public INode {

};

class IStatement: public INode {

};

class COperandExpression: public IExpression {
	IExpression* leftOperand;
	IExpression* rightOperand;
	OperandType type;
};

class CNumExpression: public IExpression {
	int number;
};

class CIdExpression: public IExpression {

};

class IVistor {
	virtual void visit(COperandExpression*) = 0;
	virtual void visit(CNumExpression*) = 0;
	virtual void visit(CIdExpression*) = 0;
};

class CPrintVisitor: public IVistor {

	void visit(COperandExpression* exp) {
		std::cout << exp->type << "\n";
		exp->leftOperand->Accept(this);
		exp->rightOperand->Accept(this);
	}

	void visit(CNumExpression* exp) {

	}
};

int main() {
	return 0;
}
