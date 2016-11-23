#include <Visitors/CInfoClasses.h>

std::ostream &operator<<(std::ostream &stream, const VariableInfo &varInfo) {
    stream << "\t\t\t\tvarDecl at " << varInfo.location;
    stream << "\t\t\t\t\tType: " << varInfo.type << "\n";
    stream << "\t\t\t\t\tName: " << varInfo.name << "\n";
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const MethodInfo &methodInfo) {
    stream << "\t\tMethod at " << methodInfo.location;
    stream << "\t\t\tName: " << methodInfo.name << "\n";
    stream << "\t\t\tRetType: " << methodInfo.returnedType << "\n";
    stream << "\t\t\tVisibility: " << methodInfo.visibility << "\n";
    stream << "\t\t\tParamList:\n";
    for(unsigned int i = 0; i < methodInfo.paramList.size(); ++i) {
        stream << methodInfo.paramList[i];
    }
    stream << "\t\t\tVarList:\n";
    for(unsigned int i = 0; i < methodInfo.variablesList.size(); ++i) {
        stream << methodInfo.variablesList[i];
    }
}

std::ostream &operator<<(std::ostream &stream, const ClassInfo &classInfo) {
    stream << "Class at " << classInfo.location;
    stream << "\tName: " << classInfo.name << "\n";
    stream << "\tBase: " << classInfo.baseId << "\n";
    stream << "\tMethods:\n";
    for(unsigned int i = 0; i < classInfo.methodsDeclarations.size(); ++i) {
        stream << classInfo.methodsDeclarations[i];
    }
    stream << "\tVarDeclarations:\n";
    for(unsigned int i = 0; i < classInfo.variableDeclaration.size(); ++i) {
        stream << classInfo.variableDeclaration[i];
    }
    stream << "\n";

}

bool ClassInfo::HasBase() {
    return baseId.length() > 0;
}


std::set<std::string> ClassInfo::getPublicMethods() {
    std::set<std::string> publicMethods;
    for (unsigned int i = 0; i < methodsDeclarations.size(); ++i) {
        if (methodsDeclarations[i].visibility == "public") {
            publicMethods.insert(methodsDeclarations[i].name);
        }
    }
    return publicMethods;
}

std::vector<MethodInfo> ClassInfo::getPublicMethodsInfo() {
    std::vector<MethodInfo> publicMethods;
    for (unsigned int i = 0; i < methodsDeclarations.size(); ++i) {
        if (methodsDeclarations[i].visibility == "public") {
            publicMethods.push_back(methodsDeclarations[i]);
        }
    }
    return publicMethods;
}