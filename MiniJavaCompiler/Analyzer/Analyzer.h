//
// Created by kagudkov on 12.11.16.
//

#ifndef MINIJAVACOMPILER_ANALYZER_H
#define MINIJAVACOMPILER_ANALYZER_H

#include <Nodes/INode.h>

class Analyzer {

public:
    Analyzer(std::shared_ptr<CProgram> program) : program(program) {}
    analyze();

private:
    std::shared_ptr<CProgram> program;

    void checkCycleInheritance();



};


#endif //MINIJAVACOMPILER_ANALYZER_H
