//
// Created by nismohl on 04.11.16.
//

#include <Nodes/CMainClass.h>

CMainClass::CMainClass(const Location location,
                       const std::shared_ptr<CIdExpression> &classId,
                       const std::shared_ptr<CMethod>& method)
        : classId(classId),
          method(method) {
    this->location = location;
}

const std::shared_ptr<CIdExpression> &CMainClass::GetClassId() const {
    return classId;
}

const std::shared_ptr<CMethod> &CMainClass::GetMainMethod() const {
    return method;
}

void CMainClass::Accept(IVisitor *visitor) {
    visitor->Visit(this);
}
