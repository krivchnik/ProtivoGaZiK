#include <CommonInclude.h>

std::string &Strings::get(int id) {
    auto it = stringIdMap.find(id);
    assert(it != stringIdMap.end());
    return it->second;
}

int Strings::add(std::string string) {
    auto it = stringMap.find(string);
    if (it == stringMap.end()) {
        int newId = stringMap.size();
        stringMap.insert(std::make_pair(string, newId));
        stringIdMap.insert(std::make_pair(newId, string));
        return newId;
    }
    return it->second;
}
