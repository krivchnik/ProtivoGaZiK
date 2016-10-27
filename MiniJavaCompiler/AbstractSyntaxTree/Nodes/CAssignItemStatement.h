#pragma once

#include <Nodes/IStatement.h>
#include <Nodes/CIdExpression.h>
//a[2] = 10
class CAssignItemStatement : public IStatement {
public:
    CAssignItemStatement(std::shared_ptr<CIdExpression> id,
                         std::shared_ptr<IExpression> expressionInBrackets,
                         std::shared_ptr<IExpression> assignedExpression);

    std::shared_ptr<CIdExpression> getId();

    std::shared_ptr<IExpression> getExpressionInBrackets();

    std::shared_ptr<IExpression> getAssignedExpression();
    void Accept(IVisitor*);
private:
    std::shared_ptr<CIdExpression> id;
    std::shared_ptr<IExpression> expressionInBrackets;
    std::shared_ptr<IExpression> assignedExpression;
};


