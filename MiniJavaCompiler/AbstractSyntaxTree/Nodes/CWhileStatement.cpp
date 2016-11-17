#include <Nodes/CWhileStatement.h>

void CWhileStatement::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}

CWhileStatement::CWhileStatement(const Location location,
                                 std::shared_ptr<IExpression> condition,
                                 std::shared_ptr<IStatement> body)
        : condition(condition),
          body(body) {

    this->location = location;
}

std::shared_ptr<IExpression> CWhileStatement::getCondition()  {
    return condition;
}

std::shared_ptr<IStatement> CWhileStatement::getBody()  {
    return body;
}
