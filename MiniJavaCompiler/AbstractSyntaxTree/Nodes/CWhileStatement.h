#pragma once

#include <Nodes/IStatement.h>
#include <Nodes/IExpression.h>

class CWhileStatement : public IStatement {
public:
    CWhileStatement(const Location location,
                    std::shared_ptr<IExpression> condition,
                    std::shared_ptr<IStatement> body);

    std::shared_ptr<IExpression> getCondition();

    std::shared_ptr<IStatement> getBody();

    void Accept(IVisitor* );

private:
    //условие цикла
    std::shared_ptr<IExpression> condition;
    //тело цикла
    std::shared_ptr<IStatement> body;
};

