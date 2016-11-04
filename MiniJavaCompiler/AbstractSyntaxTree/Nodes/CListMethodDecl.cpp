//
// Created by nismohl on 03.11.16.
//

#include <Nodes/CListMethodDecl.h>

void CListMethodDecl::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}

void CListMethodDecl::Add(std::shared_ptr<CMethod> declaration) {
    declarations.push_back(declaration);
}

const std::vector<std::shared_ptr<CMethod>> &CListMethodDecl::GetDeclarations() const {
    return declarations;
}

