#include <Visitors/CInfoClasses.h>

void VariableInfo::Print(std::ostream& stream) {
    stream << "\t        varDecl:" << std::endl;
    location.Print(stream);
    stream << "\t        Type  " << strings.get(typeId) << " Name  " << strings.get(nameId) << std::endl;
}

void MethodInfo::Print(std::ostream& stream) {
    stream << "\t    Method:" << std::endl;
    stream << "\t    Name  " << strings.get(nameId) << std::endl;
    location.Print(stream);
    stream << "\t    RetType " << strings.get(returnedTypeId) << std::endl;
    stream << "\t    Visibility " << (isPublic ? "public" : "private") << std::endl;
    stream << "\t    ParamList" << std::endl;
    for(unsigned int i = 0; i < paramList.size(); ++i) {
        paramList[i].Print(stream);
    }
    stream << "\t    VarList" << std::endl;
    for(unsigned int i = 0; i < variablesList.size(); ++i) {
        variablesList[i].Print(stream);
    }
}

void ClassInfo::Print(std::ostream& stream) {
    stream << "Class " << std::endl;
    stream << "Name " << strings.get(nameId) << std::endl;
    location.Print(stream);
    stream << "Base " << strings.get(baseId) << std::endl;
    stream << "Methods " << std::endl;
    for(unsigned int i = 0; i < methodsDeclarations.size(); ++i) {
        methodsDeclarations[i].Print(stream);
    }
    stream << "VarDeclarations " << std::endl;
    for(unsigned int i = 0; i < variableDeclaration.size(); ++i) {
        variableDeclaration[i].Print(stream);
    }

}

bool ClassInfo::HasBase() {
    return strings.get(baseId).length() > 0;
}


std::set<int> ClassInfo::getPublicMethods() {
    std::set<int> publicMethods;
    for (unsigned int i = 0; i < methodsDeclarations.size(); ++i) {
        if (methodsDeclarations[i].isPublic) {
            publicMethods.insert(methodsDeclarations[i].nameId);
        }
    }
    return publicMethods;
}

std::vector<MethodInfo> ClassInfo::getPublicMethodsInfo() {
    std::vector<MethodInfo> publicMethods;
    for (unsigned int i = 0; i < methodsDeclarations.size(); ++i) {
        if (methodsDeclarations[i].isPublic) {
            publicMethods.push_back(methodsDeclarations[i]);
        }
    }
    return publicMethods;
}