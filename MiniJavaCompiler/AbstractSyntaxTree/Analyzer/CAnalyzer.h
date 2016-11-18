#pragma  once
#include <CommonInclude.h>

class CAnalyzer {

public:
    CAnalyzer(std::shared_ptr<CProgram> program);
    void analyze();

private:
    std::shared_ptr<CProgram> program;
    std::map< std::string, ClassInfo > classes;
    //проверка циклических наследований
    void checkCycleInheritance();
    //проверка переопределения методов
    void checkMethodOverrides();
    //запуск CheckVisitor
    std::set<std::string> checkTypes();
};


