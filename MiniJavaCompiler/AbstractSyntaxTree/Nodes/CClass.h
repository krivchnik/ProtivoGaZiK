//
// Created by nismohl on 03.11.16.
//

#pragma once

#include <Nodes/IStatement.h>
#include <Nodes/CListVarDecl.h>
#include <Nodes/CListMethodDecl.h>

class CClass : public IStatement {
public:
    CClass( const std::shared_ptr<CIdExpression> &id,
            const std::shared_ptr<CListVarDecl> &fields, const std::shared_ptr<CListMethodDecl> &methods);

    CClass( const std::shared_ptr<CIdExpression> &id, const std::shared_ptr<CIdExpression> &baseId,
            const std::shared_ptr<CListVarDecl> &fields, const std::shared_ptr<CListMethodDecl> &methods);

    const std::shared_ptr<CIdExpression> &getId() const;

    const std::shared_ptr<CIdExpression> &getBaseId() const;

    const std::shared_ptr<CListVarDecl> &getFields() const;

    const std::shared_ptr<CListMethodDecl> &getMethods() const;

    void Accept(IVisitor*);
private:
    std::shared_ptr<CIdExpression> id;
    std::shared_ptr<CIdExpression> baseId;
    std::shared_ptr<CListVarDecl> fields;
    std::shared_ptr<CListMethodDecl> methods;
};
