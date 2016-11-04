//
// Created by nismohl on 04.11.16.
//

#include "CMainClass.h"

CMainClass::CMainClass(const std::shared_ptr<CIdExpression> &classId, const std::shared_ptr<CIdExpression> &argId,
                       const std::shared_ptr<IStatement> &statement)
        : classId(classId), argId(argId), statement(statement) {}

const std::shared_ptr<CIdExpression> &CMainClass::GetClassId() const {
    return classId;
}

const std::shared_ptr<CIdExpression> &CMainClass::GetArgId() const {
    return argId;
}

const std::shared_ptr<IStatement> &CMainClass::GetStatement() const {
    return statement;
}

void CMainClass::Accept(IVisitor *visitor) {
    visitor->Visit(this);
}

