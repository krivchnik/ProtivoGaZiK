//
// Created by kagudkov on 12.11.16.
//

#include <Analyzer/CAnalyzer.h>

#include <iostream>
#include <Visitors/CValidateVisitor.h>

void CAnalyzer::analyze() {
    checkCycleInheritance();

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
    std::vector<std::shared_ptr<CClass> > classesValues;
    std::map<std::shared_ptr<CClass>, bool> used;
    for( auto iter = classes.begin(); iter != classes.end(); ++iter ){
        classesValues.push_back( iter->second );
        used[iter->second] = false;
    }
    for( auto iter = used.begin(); iter != used.end(); ++iter ) {
        if( !iter->second ) {
            iter->second = true;
            std::shared_ptr<CClass> nextClass = iter->first;
            //TODO
            // while( nextClass->getBaseId() != nullptr && !used[classes[nextClass->getBaseId()]] ) {
               // nextClass = classes[nextClass->getBaseId()];
             //   used[nextClass] = true;
            //}
            if( nextClass->getBaseId() != nullptr && used[classes[nextClass->getBaseId()]] ) {
                std::cout << "recursive inheritance " << nextClass->getBaseId()->GetName() << " ->"
                          << nextClass->getBaseId() << std::endl;
            }
        }
    }
}

std::set<std::string> CAnalyzer::checkTypes() {

    CValidateVisitor validateVisitor;
    validateVisitor.Visit(program.get());
    return std::set<std::string>();
}
