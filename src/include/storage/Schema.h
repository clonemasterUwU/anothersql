
#ifndef ANOTHERSQL_SCHEMA_H
#define ANOTHERSQL_SCHEMA_H

#include <vector>
#include <string>
#include "_macro.h"

class Schema {
    std::vector<std::string> fieldNames;
    std::vector<i32> fieldTypes;
};


#endif //ANOTHERSQL_SCHEMA_H
