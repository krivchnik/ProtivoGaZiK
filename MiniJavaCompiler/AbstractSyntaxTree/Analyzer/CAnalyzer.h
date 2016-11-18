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
    //проверить, что переменые не переопределяются
    void checkVariableOverrides();
    //вернуть список доступных переменных из класса
    std::vector<std::string> getAvailVariables(ClassInfo classInfo);
    //запуск CheckVisitor
    std::set<std::string> checkTypes();
};


