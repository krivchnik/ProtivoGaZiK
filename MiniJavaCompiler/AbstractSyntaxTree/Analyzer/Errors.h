#pragma once

#include <map>
#include <vector>
#include <ostream>

#include <Nodes/INode.h>

enum ErrorType {
    UNDEFINED_VARIABLE,
    UNKNOWN_TYPE,
    PRIVATE_METHOD_CALL,
    NON_BOOLEAN_EXP,
    NON_INTEGER,
    NON_ARRAY
};

std::ostream& operator<< (std::ostream& out, const ErrorType error);

struct ErrorDescription {
    Location loc;
    ErrorType type;

    //additional info: variable name, exp type, etc.
    std::string info;
};

class Errors {
public:

    void AddError(const ErrorDescription& desc) {
        errors.push_back(desc);
    }

    const std::vector<ErrorDescription>& GetErrors() const {
        return errors;
    }

private:
    std::vector<ErrorDescription> errors;
};


