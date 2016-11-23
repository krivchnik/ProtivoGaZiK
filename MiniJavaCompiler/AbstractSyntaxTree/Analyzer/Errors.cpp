#include <Analyzer/Errors.h>

std::ostream& operator<< (std::ostream& out, const ErrorType error) {
    static std::map<ErrorType, std::string> messages;
    if (messages.size() == 0) {
        messages[UNDEFINED_IDENTIFIER] = "[unknown identifier]";
        messages[UNKNOWN_TYPE] = "[unknown type]";
        messages[PRIVATE_METHOD_CALL] = "[private method call]";
        messages[NON_BOOLEAN_EXP] = "[expression must be boolean]";
        messages[NON_INTEGER] = "[expression must be integer]";
        messages[NON_ARRAY] = "[must have array type]";
        messages[REDEFINITION_CLASS] = "[class redefinition]";
        messages[REDEFINITION_METHOD] = "[method redefinition]";
        messages[REDEFINITION_PARAM] = "[param redefinition]";
        messages[RECURSIVE_INHERITANCE] = "[recursive class inheritance]";
        messages[WRONG_TYPE] = "[wrong type]";
        messages[WRONG_ARGUMENT_NUMBER] = "[wrong number of arguments]";
    }
    return out << messages[error];
}

