//
// Created by nismohl on 12.11.16.
//

#include <Nodes/CMethodCallExpression.h>

CMethodCallExpression::CMethodCallExpression(const std::shared_ptr<IExpression> &object,
                                             const std::shared_ptr<CIdExpression> &methodId,
                                             const std::shared_ptr<CListExpression> &arguments):
        object(object), methodId(methodId), arguments(arguments) {}

void CMethodCallExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}

const std::shared_ptr<IExpression> &CMethodCallExpression::getObject() const {
    return object;
}

const std::shared_ptr<CIdExpression> &CMethodCallExpression::getMethodId() const {
    return methodId;
}

const std::shared_ptr<CListExpression> &CMethodCallExpression::getArguments() const {
    return arguments;
}
