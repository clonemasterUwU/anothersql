#ifndef ANOTHERSQL_LOCK_H
#define ANOTHERSQL_LOCK_H

#include <functional>
#include "_macro.h"
#include "ResourceName.h"
#include "LockType.h"

class Lock {
private:
    std::reference_wrapper<const ResourceName> _resourceName;
    LockType lt;
    i64 transactionNum;

    friend class ResourceEntry;
    friend class LockManager;
public:
    Lock(const ResourceName &resourceName, LockType lt, i64 transactionNum);

    bool operator==(const Lock &rhs) const;

    bool operator!=(const Lock &rhs) const;
};


#endif //ANOTHERSQL_LOCK_H
