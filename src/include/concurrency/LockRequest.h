#ifndef ANOTHERSQL_LOCKREQUEST_H
#define ANOTHERSQL_LOCKREQUEST_H

#include <vector>
#include "Lock.h"

class TransactionContext;

class LockRequest {
private:
    std::reference_wrapper<const TransactionContext> transaction;
    Lock lock;
    std::vector<Lock> releaseLocks;

    friend class LockManager;

    friend class ResourceEntry;

public:
    LockRequest(const TransactionContext &transaction, Lock lock, std::vector<Lock> releasedLock = std::vector<Lock>());
};


#endif //ANOTHERSQL_LOCKREQUEST_H
