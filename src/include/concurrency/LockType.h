#ifndef ANOTHERSQL_LOCKTYPE_H
#define ANOTHERSQL_LOCKTYPE_H

#include <ostream>
enum LockType {
    S,
    X,
    IS,
    IX,
    SIX,
    NL,
};

std::ostream & operator << (std::ostream& out,LockType lt);
namespace LT {
    bool compatible(LockType a, LockType b);
    LockType parentLock(LockType lt);
    bool canBeParentLock(LockType parent,LockType child);
    bool substitutable(LockType substitute,LockType required);

}

#endif //ANOTHERSQL_LOCKTYPE_H
