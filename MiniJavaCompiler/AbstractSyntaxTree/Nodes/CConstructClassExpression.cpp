//
// Created by kagudkov on 28.10.16.
//

#include "CConstructClassExpression.h"

CConstructClassExpression::CConstructClassExpression(const std::shared_ptr<CIdExpression> &classID) : classID(
        classID) {}

const std::shared_ptr<CIdExpression> &CConstructClassExpression::getClassID() const {
    return classID;
}

void CConstructClassExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}
