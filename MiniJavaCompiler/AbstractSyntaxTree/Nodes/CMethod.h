#pragma once

#include <Nodes/IStatement.h>
#include <Nodes/IExpression.h>
#include <Nodes/CIdExpression.h>
#include <Nodes/CListStatement.h>
#include <Nodes/CListVarDecl.h>

class CMethod : public IStatement {
public:
    CMethod(const std::shared_ptr<CIdExpression> &visibility, const std::string &typeName,
            const std::shared_ptr<CIdExpression> &id, const std::shared_ptr<CListVarDecl> &parameters,
            const std::shared_ptr<CListVarDecl> &listDeclarations,
            const std::shared_ptr<CListStatement> &listStatements,
            const std::shared_ptr<IExpression> &returnExpression);

private:
    std::shared_ptr<CIdExpression> visibility;
    std::string typeName;
    std::shared_ptr<CIdExpression> id;
    std::shared_ptr<CListVarDecl> parameters;
    std::shared_ptr<CListVarDecl> listDeclarations;
    std::shared_ptr<CListStatement> listStatements;
    std::shared_ptr<IExpression> returnExpression;

};
