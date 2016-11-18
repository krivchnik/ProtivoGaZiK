//
// Created by kagudkov on 12.11.16.
//

#include <Analyzer/CAnalyzer.h>


void CAnalyzer::analyze() {
    checkCycleInheritance();
    checkMethodOverrides();
    checkTypes();
}

CAnalyzer::CAnalyzer(std::shared_ptr<CProgram> program) : program(program) {
    CGetClassesVisitor getClassesVisitor;
    getClassesVisitor.Visit(program.get());
    classes = getClassesVisitor.getClasses();
    for(auto it = classes.begin(); it != classes.end(); ++it) {
        it->second.Print(std::cout);
    }
}

void CAnalyzer::checkCycleInheritance() {
    //те вершины которые мы уже видели
    std::map<std::string, bool> used;
    for(auto it = classes.begin(); it != classes.end(); ++it) {
        used[it->first] = false;
    }
    for(auto it = classes.begin(); it != classes.end(); ++it) {
        if( !used[it->first]) {
            used[it->first] = true;
            std::vector<std::string> nameOfClassedInChain;
            std::string nextBaseName = it->first;
            nameOfClassedInChain.push_back(nextBaseName);
            while( classes[nextBaseName].HasBase() ) {
                nextBaseName = classes[nextBaseName].baseId;
                nameOfClassedInChain.push_back(nextBaseName);
                if( used[nextBaseName] ){
                    std::cout << "Recursive inheritance " << nameOfClassedInChain[0];
                    for(size_t i = 1; i < nameOfClassedInChain.size(); ++i ){
                        std::cout << " -> " << nameOfClassedInChain[i];
                    }
                    break;
                }
                used[nextBaseName] = true;
            }
        }
    }

}

std::set<std::string> CAnalyzer::checkTypes() {

    CCheckTypesVisitor checkTypesVisitor(classes);
    checkTypesVisitor.Visit(program.get());
    return std::set<std::string>();
}

void CAnalyzer::checkMethodOverrides() {

}
