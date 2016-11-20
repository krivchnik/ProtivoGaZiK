#pragma once

#include <vector>

#include <Nodes/INode.h>

enum ErrorType {
    UNDEFINED_VARIABLE,
    UNKNOWN_TYPE,
    PRIVATE_METHOD_CALL,
    NON_BOOLEAN_EXP,
    NON_INTEGER,
    NON_ARRAY
};

struct ErrorDescription {
    Location loc;
    ErrorType type;
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


