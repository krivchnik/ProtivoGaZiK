#pragma once

#include <Nodes/IStatement.h>
#include <Nodes/IExpression.h>
#include <Nodes/CIdExpression.h>
#include <Nodes/CListStatement.h>

class CMethod : public IStatement {
public:
    CMethod(const Location location,
            const bool isPublic, const std::string &typeName,
            const std::shared_ptr<CIdExpression> &id, const std::shared_ptr<CListStatement> &parameters,
            const std::shared_ptr<CListStatement> &listDeclarations,
            const std::shared_ptr<CListStatement> &listStatements,
            const std::shared_ptr<IExpression> &returnExpression);

    bool getVisibility() const;

    const std::string &getTypeName() const;
    int getTypeNameId() { return typeNameId; }

    const std::shared_ptr<CIdExpression> &getId() const;

    const std::shared_ptr<CListStatement> &getParameters() const;

    const std::shared_ptr<CListStatement> &getListDeclarations() const;

    const std::shared_ptr<CListStatement> &getListStatements() const;

    const std::shared_ptr<IExpression> &getReturnExpression() const;

    void Accept(IVisitor*);
private:
    bool isPublic;
    int typeNameId;
    std::shared_ptr<CIdExpression> id;
    std::shared_ptr<CListStatement> parameters;
    std::shared_ptr<CListStatement> listDeclarations;
    std::shared_ptr<CListStatement> listStatements;
    std::shared_ptr<IExpression> returnExpression;

};
