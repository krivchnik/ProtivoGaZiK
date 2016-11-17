//
// Created by nismohl on 03.11.16.
//

#include "CClass.h"

CClass::CClass( const Location location,
                const std::shared_ptr<CIdExpression> &id,
                const std::shared_ptr<CListStatement> &fields, const std::shared_ptr<CListStatement> &methods)
        : id(id), baseId(nullptr),
          fields(fields), methods(methods) {

    this->location = location;
}

CClass::CClass( const Location location,
                const std::shared_ptr<CIdExpression> &id, const std::shared_ptr<CIdExpression> &baseId,
                const std::shared_ptr<CListStatement> &fields, const std::shared_ptr<CListStatement> &methods)
        : id(id), baseId(baseId),
          fields(fields), methods(methods) {

    this->location = location;
}

const std::shared_ptr<CIdExpression> &CClass::getId() const {
    return id;
}

const std::shared_ptr<CIdExpression> &CClass::getBaseId() const {
    return baseId;
}

const std::shared_ptr<CListStatement> &CClass::getFields() const {
    return fields;
}

const std::shared_ptr<CListStatement> &CClass::getMethods() const {
    return methods;
}

void CClass::Accept(IVisitor *visitor) {
    visitor->Visit(this);
}

void CClass::setId(const std::shared_ptr<CIdExpression> &id) {
    CClass::id = id;
}

void CClass::setBaseId(const std::shared_ptr<CIdExpression> &baseId) {
    CClass::baseId = baseId;
}


