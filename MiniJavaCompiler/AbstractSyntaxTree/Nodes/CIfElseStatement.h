#ifndef MINIJAVACOMPILER_CIFELSESTATEMENT_H
#define MINIJAVACOMPILER_CIFELSESTATEMENT_H


#include <Nodes/IExpression.h>
#include <Nodes/IStatement.h>

class CIfElseStatement {
public:

private:
public:
    const std::shared_ptr<IExpression> &getExpression() const;

    const std::shared_ptr<IStatement> &getIfStatement() const;

    const std::shared_ptr<IStatement> &getElseStatement() const;

public:
    CIfElseStatement(const std::shared_ptr<IExpression> &expression, const std::shared_ptr<IStatement> &ifStatement,
                     const std::shared_ptr<IStatement> &elseStatement);

private:
    std::shared_ptr<IExpression> expression;
    std::shared_ptr<IStatement> ifStatement;
    std::shared_ptr<IStatement> elseStatement;
};


#endif //MINIJAVACOMPILER_CIFELSESTATEMENT_H
