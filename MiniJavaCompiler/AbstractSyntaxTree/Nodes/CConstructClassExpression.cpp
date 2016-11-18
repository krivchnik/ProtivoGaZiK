//
// Created by kagudkov on 28.10.16.
//

#include <Nodes/CConstructClassExpression.h>

CConstructClassExpression::CConstructClassExpression(const Location location,
                                                     const std::shared_ptr<CIdExpression> &classID)
        : classID(classID) {
    this->location = location;
    this->type = this->classID->GetName();
}

const std::shared_ptr<CIdExpression> &CConstructClassExpression::getClassID() const {
    return classID;
}

void CConstructClassExpression::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}
