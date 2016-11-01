//
// Created by nismohl on 01.11.16.
//

#include <Nodes/CListVarDecl.h>

void CListVarDecl::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}

void CListVarDecl::Add(std::shared_ptr<CVarDecl> declaration) {
    declarations.push_back(declaration);
}

const std::vector<std::shared_ptr<CVarDecl>> &CListVarDecl::GetDeclarations() const {
    return declarations;
}
