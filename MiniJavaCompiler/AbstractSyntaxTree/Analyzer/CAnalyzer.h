#pragma  once
#include <CommonInclude.h>
#include <Visitors/CSymbolTable.h>

class CAnalyzer {

public:
    CAnalyzer(std::shared_ptr<CProgram> program);

    std::vector<ErrorDescription> analyze();

    CSymbolTable GetSymbolTable() const {
        return CSymbolTable(classes);
    }
private:
    std::shared_ptr<CProgram> program;
    std::map< std::string, ClassInfo > classes;
    //проверка циклических наследований
    void checkCycleInheritance();
    //проверка переопределения методов
    void checkMethodOverrides();
    //проверить, что параметры не переопределяются
    void checkParamOverrides();
    //проверить, что переменые не переопределяются
    void checkVariableOverrides();
    //вернуть список доступных переменных из класса
    std::vector<std::string> getAvailVariables(ClassInfo classInfo);

    //запуск CheckVisitor
    void checkTypes();

    std::vector<ErrorDescription> errors;
};


