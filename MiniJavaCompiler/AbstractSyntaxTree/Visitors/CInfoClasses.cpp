#include <Visitors/CInfoClasses.h>

void VariableInfo::Print(std::ostream& stream) {
    stream << "\        varDecl:" << std::endl;
    stream << "\        Type  " << type << " Name  " << name << std::endl;
}

void MethodInfo::Print(std::ostream& stream) {
    stream << "\    Method:" << std::endl;
    stream << "\    Name  " << name << std::endl;
    stream << "\    RetType " << returnedType << std::endl;
    stream << "\    Visibility " << visibility << std::endl;
    stream << "\    ParamList" << std::endl;
    for(int i = 0; i < paramList.size(); ++i) {
        paramList[i].Print(stream);
    }
    stream << "\    VarList" << std::endl;
    for(int i = 0; i < variablesList.size(); ++i) {
        variablesList[i].Print(stream);
    }
}

void ClassInfo::Print(std::ostream& stream) {
    stream << "Class " << std::endl;
    stream << "Name " << name << std::endl;
    stream << "Base " << baseId << std::endl;
    stream << "Methods " << std::endl;
    for(int i = 0; i < methodsDeclarations.size(); ++i) {
        methodsDeclarations[i].Print(stream);
    }
    stream << "VarDeclarations " << std::endl;
    for(int i = 0; i < variableDeclaration.size(); ++i) {
        variableDeclaration[i].Print(stream);
    }

}

bool ClassInfo::HasBase() {
    return baseId.length() > 0;
}
