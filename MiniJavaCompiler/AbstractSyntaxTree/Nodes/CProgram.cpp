//
// Created by nismohl on 04.11.16.
//

#include "CProgram.h"

CProgram::CProgram(const std::shared_ptr<CMainClass> &mainClass, const std::shared_ptr<CListStatement> &minorClasses)
        : mainClass(mainClass), minorClasses(minorClasses) {}

const std::shared_ptr<CMainClass> &CProgram::GetMainClass() const {
    return mainClass;
}

const std::shared_ptr<CListStatement> &CProgram::GetMinorClasses() const {
    return minorClasses;
}

void CProgram::Accept(IVisitor *visitor) {
    visitor->Visit(this);
}

