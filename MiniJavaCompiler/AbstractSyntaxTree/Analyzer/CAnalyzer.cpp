//
// Created by kagudkov on 12.11.16.
//

#include <Analyzer/CAnalyzer.h>

#include <iostream>

void CAnalyzer::analyze() {


}

CAnalyzer::CAnalyzer(std::shared_ptr<CProgram> program) : program(program) {
    CGetClassesVisitor getClassesVisitor;
    getClassesVisitor.Visit(program.get());
    classes = getClassesVisitor.getClasses();
    for (auto it = classes.begin(); it != classes.end(); ++it) {
        std::cout << it->first->GetName() << "\n";
    }
}

void CAnalyzer::checkCycleInheritance() {

}
