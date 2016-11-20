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
    }
    return out << messages[error];
}

