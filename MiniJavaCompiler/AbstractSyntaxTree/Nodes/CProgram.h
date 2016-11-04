//
// Created by nismohl on 04.11.16.
//

#pragma once

#include <Nodes/INode.h>
#include <Nodes/CMainClass.h>
#include <Nodes/CListStatement.h>

class CProgram: public INode {
public:
    CProgram(const std::shared_ptr<CMainClass> &mainClass, const std::shared_ptr<CListStatement> &minorClasses);

    const std::shared_ptr<CMainClass> &GetMainClass() const;
    const std::shared_ptr<CListStatement> &GetMinorClasses() const;

    void Accept(IVisitor*);

private:
    std::shared_ptr<CMainClass> mainClass;
    std::shared_ptr<CListStatement> minorClasses;
};


