//
// Created by nismohl on 04.11.16.
//

#pragma once

#include <Nodes/IStatement.h>
#include <Nodes/CIdExpression.h>

class CMainClass : public IStatement {
public:
    CMainClass(const Location location,
               const std::shared_ptr<CIdExpression> &classId,
               const std::shared_ptr<CIdExpression> &argId,
               const std::shared_ptr<IStatement> &statement);

    const std::shared_ptr<CIdExpression> &GetClassId() const;

    const std::shared_ptr<CIdExpression> &GetArgId() const;

    const std::shared_ptr<IStatement> &GetStatement() const;

    void Accept(IVisitor*);

private:
    std::shared_ptr<CIdExpression> classId;
    std::shared_ptr<CIdExpression> argId;
    std::shared_ptr<IStatement> statement;
};

