//
// Created by nismohl on 04.11.16.
//

#include <Nodes/CProgram.h>

CProgram::CProgram(const Location location,
                   const std::shared_ptr<CMainClass> &mainClass,
                   const std::shared_ptr<CListStatement> &minorClasses)
        : mainClass(mainClass),
          minorClasses(minorClasses) {
    this->location = location;
}

const std::shared_ptr<CMainClass> &CProgram::GetMainClass() const {
    return mainClass;
}

const std::shared_ptr<CListStatement> &CProgram::GetMinorClasses() const {
    return minorClasses;
}

void CProgram::Accept(IVisitor *visitor) {
    visitor->Visit(this);
}

