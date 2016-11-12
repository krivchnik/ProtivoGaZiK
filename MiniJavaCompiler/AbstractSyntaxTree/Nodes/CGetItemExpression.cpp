//
// Created by nismohl on 12.11.16.
//

#include <Nodes/CGetItemExpression.h>

CGetItemExpression::CGetItemExpression(const std::shared_ptr<IExpression> &object,
                                       const std::shared_ptr<IExpression> &index)
        : object(object), index(index) {}

const std::shared_ptr<IExpression> &CGetItemExpression::GetObject() const {
    return object;
}

const std::shared_ptr<IExpression> &CGetItemExpression::GetIndex() const {
    return index;
}

void CGetItemExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}
