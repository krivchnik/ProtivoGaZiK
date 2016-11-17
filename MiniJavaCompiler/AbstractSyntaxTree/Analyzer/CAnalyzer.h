#pragma  once
#include <Nodes/INode.h>
#include <Visitors/CGetClassesVisitor.h>

class CAnalyzer {

public:
    CAnalyzer(std::shared_ptr<CProgram> program);
    void analyze();

private:
    std::shared_ptr<CProgram> program;
    std::map< std::string, ClassInfo > classes;
    void checkCycleInheritance();



};


