//
// Created by kagudkov on 03.11.16.
//

#include <Nodes/CMethod.h>

CMethod::CMethod(const std::shared_ptr<CIdExpression> &visibility, const std::string &typeName,
                 const std::shared_ptr<CIdExpression> &id, const std::shared_ptr<CListVarDecl> &parameters,
                 const std::shared_ptr<CListVarDecl> &listDeclarations,
                 const std::shared_ptr<CListStatement> &listStatements,
                 const std::shared_ptr<IExpression> &returnExpression) : visibility(visibility), typeName(typeName),
                                                                         id(id), parameters(parameters),
                                                                         listDeclarations(listDeclarations),
                                                                         listStatements(listStatements),
                                                                         returnExpression(returnExpression) {}
