#pragma once

#include <string>
#include <map>

class Strings {
public:
    std::string &get(int id);
    int add(std::string string);

private:
    std::map<int, std::string> stringIdMap;
    std::map<std::string, int> stringMap;
};
