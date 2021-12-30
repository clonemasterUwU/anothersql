#ifndef ANOTHERSQL_RESOURCENAME_H
#define ANOTHERSQL_RESOURCENAME_H


#include <vector>
#include <string>
#include <ostream>
#include "_macro.h"

class ResourceName {
private:
    std::vector<std::string_view> names;

    friend class ResourceNameHash;

public:
    ResourceName(std::string_view name) {
        names.push_back(name);
    }

    ResourceName(std::vector<std::string_view> names) : names(std::move(names)) {};

    ResourceName(const ResourceName &parent, std::string_view name) : names(parent.names) {
        names.push_back(name);
    }

    bool isDescendantOf(const ResourceName &ancestor) {
        if (ancestor.names.size() >= names.size()) return false;
        for (int i = 0; i < ancestor.names.size(); i++) {
            if (names[i] != ancestor.names[i]) return false;
        }
        return true;
    }

    bool operator==(const ResourceName &rhs) const {
        return names == rhs.names;
    }

    bool operator!=(const ResourceName &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const ResourceName &name) {
        os << "names: " << name.names;
        return os;
    }
};

struct ResourceNameHash {
    std::size_t operator()(const ResourceName &resourceName) const {
        std::size_t seed = resourceName.names.size();
        for (auto &i: resourceName.names) {
            seed ^= std::hash<std::string_view>()(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    };
};


#endif //ANOTHERSQL_RESOURCENAME_H
