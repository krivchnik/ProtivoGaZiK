//
// Created by kagudkov on 03.11.16.
//

#include <Nodes/CMethod.h>

CMethod::CMethod(const Location location,
                 const bool isPublic, const std::string &typeName,
                 const std::shared_ptr<CIdExpression> &id, const std::shared_ptr<CListStatement> &parameters,
                 const std::shared_ptr<CListStatement> &listDeclarations,
                 const std::shared_ptr<CListStatement> &listStatements,
                 const std::shared_ptr<IExpression> &returnExpression)
        : isPublic(isPublic), id(id), parameters(parameters),
          listDeclarations(listDeclarations),
          listStatements(listStatements),
          returnExpression(returnExpression) {
    typeNameId = strings.add(typeName);
    this->location = location;
}

void CMethod::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}

bool CMethod::getVisibility() const {
    return isPublic;
}

const std::string &CMethod::getTypeName() const {
    return strings.get(typeNameId);
}

const std::shared_ptr<CIdExpression> &CMethod::getId() const {
    return id;
}

const std::shared_ptr<CListStatement> &CMethod::getParameters() const {
    return parameters;
}

const std::shared_ptr<CListStatement> &CMethod::getListDeclarations() const {
    return listDeclarations;
}

const std::shared_ptr<CListStatement> &CMethod::getListStatements() const {
    return listStatements;
}

const std::shared_ptr<IExpression> &CMethod::getReturnExpression() const {
    return returnExpression;
}
