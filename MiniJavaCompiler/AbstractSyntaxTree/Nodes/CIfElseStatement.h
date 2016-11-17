#pragma once

#include <Nodes/IExpression.h>
#include <Nodes/IStatement.h>

class CIfElseStatement : public IStatement {

public:
    const std::shared_ptr<IExpression> &getExpression() const;

    const std::shared_ptr<IStatement> &getIfStatement() const;

    const std::shared_ptr<IStatement> &getElseStatement() const;

    CIfElseStatement(const Location location,
                     const std::shared_ptr<IExpression> &expression,
                     const std::shared_ptr<IStatement> &ifStatement,
                     const std::shared_ptr<IStatement> &elseStatement);

    void Accept(IVisitor* visitor);


private:
    std::shared_ptr<IExpression> expression;
    std::shared_ptr<IStatement> ifStatement;
    std::shared_ptr<IStatement> elseStatement;
};