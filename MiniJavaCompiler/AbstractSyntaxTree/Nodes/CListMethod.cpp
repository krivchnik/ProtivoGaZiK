//
// Created by kagudkov on 03.11.16.
//

#include "CListMethod.h"

CListMethod::CListMethod() {
}

const std::vector<std::shared_ptr<IStatement>> &CListMethod::GetMethods() const {
    return methods;
}

void CListMethod::Add(std::shared_ptr<IStatement> method) {
    methods.push_back(method);
}

void CListMethod::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}
