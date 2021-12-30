#ifndef ANOTHERSQL__MACRO_H
#define ANOTHERSQL__MACRO_H
#include <cstdint>
#include <ostream>
#include <vector>
#include <deque>
typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int32_t i32;
typedef int64_t i64;
typedef float f32;
typedef double f64;
template<class T>
std::ostream &operator<<(std::ostream &os,const std::vector<T>& v);

template<class T>
std::ostream &operator<<(std::ostream &os,const std::deque<T>& d);

#endif //ANOTHERSQL__MACRO_H
