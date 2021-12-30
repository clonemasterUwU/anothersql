#include "concurrency/Lock.h"

Lock::Lock(const ResourceName &resourceName, LockType lt, i64 transactionNum) :
        _resourceName(resourceName), lt(lt), transactionNum(transactionNum) {}

bool Lock::operator==(const Lock &rhs) const {
    return lt == rhs.lt &&
           transactionNum == rhs.transactionNum
           && _resourceName.get() == rhs._resourceName.get();
}

bool Lock::operator!=(const Lock &rhs) const {
    return !(rhs == *this);
}
