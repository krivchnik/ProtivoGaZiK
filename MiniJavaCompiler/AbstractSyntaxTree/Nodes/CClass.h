//
// Created by nismohl on 03.11.16.
//
#pragma once

#include <Nodes/IStatement.h>
#include <Nodes/CIdExpression.h>
#include <Nodes/CListStatement.h>

class CClass : public IStatement {
public:
    CClass( const Location location,
            const std::shared_ptr<CIdExpression> &id,
            const std::shared_ptr<CListStatement> &fields, const std::shared_ptr<CListStatement> &methods);

    CClass( const Location location,
            const std::shared_ptr<CIdExpression> &id, const std::shared_ptr<CIdExpression> &baseId,
            const std::shared_ptr<CListStatement> &fields, const std::shared_ptr<CListStatement> &methods);

    const std::shared_ptr<CIdExpression> &getId() const;

    const std::shared_ptr<CIdExpression> &getBaseId() const;

    const std::shared_ptr<CListStatement> &getFields() const;

    const std::shared_ptr<CListStatement> &getMethods() const;

    void setId(const std::shared_ptr<CIdExpression> &id);

    void setBaseId(const std::shared_ptr<CIdExpression> &baseId);

    void Accept(IVisitor*);
private:
    std::shared_ptr<CIdExpression> id;
    std::shared_ptr<CIdExpression> baseId;
    std::shared_ptr<CListStatement> fields;
    std::shared_ptr<CListStatement> methods;
};
