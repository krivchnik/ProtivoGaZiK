//
// Created by kagudkov on 23.10.16.
//

#include "CIfElseStatement.h"

CIfElseStatement::CIfElseStatement(const Location location,
                                   const std::shared_ptr<IExpression> &expression,
                                   const std::shared_ptr<IStatement> &ifStatement,
                                   const std::shared_ptr<IStatement> &elseStatement)
        : expression(expression),
          ifStatement(ifStatement),
          elseStatement(elseStatement) {
    this->location = location;
}

const std::shared_ptr<IExpression> &CIfElseStatement::getExpression() const {
    return expression;
}

const std::shared_ptr<IStatement> &CIfElseStatement::getIfStatement() const {
    return ifStatement;
}

const std::shared_ptr<IStatement> &CIfElseStatement::getElseStatement() const {
    return elseStatement;
}

void CIfElseStatement::Accept(IVisitor * visitor) {
    visitor->Visit(this);
}
