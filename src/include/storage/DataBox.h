#ifndef ANOTHERSQL_DATABOX_H
#define ANOTHERSQL_DATABOX_H

#include <variant>
#include <fstream>
#include <string>
#include "_macro.h"

using DataBox = std::variant<i32, i64, f32, f64, bool, std::pair<u32,std::string>>;

DataBox fromBinary(std::ifstream &inFile, u32 index);

void toBinary(std::ofstream &inFile, const DataBox &value);

#endif //ANOTHERSQL_DATABOX_H
