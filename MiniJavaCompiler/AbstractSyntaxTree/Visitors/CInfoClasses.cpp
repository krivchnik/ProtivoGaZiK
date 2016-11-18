#include <Visitors/CInfoClasses.h>

void VariableInfo::Print(std::ostream& stream) {
    stream << "\        varDecl:" << std::endl;
    location.Print(stream);
    stream << "\        Type  " << type << " Name  " << name << std::endl;
}

void MethodInfo::Print(std::ostream& stream) {
    stream << "\    Method:" << std::endl;
    stream << "\    Name  " << name << std::endl;
    location.Print(stream);
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
    location.Print(stream);
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


std::set<std::string> ClassInfo::getPublicMethods() {
    std::set<std::string> publicMethods;
    for (int i = 0; i < methodsDeclarations.size(); ++i) {
        if (methodsDeclarations[i].visibility == "public") {
            publicMethods.insert(methodsDeclarations[i].name);
        }
    }
    return publicMethods;
}

