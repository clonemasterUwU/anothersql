#ifndef ANOTHERSQL_RESOURCEENTRY_H
#define ANOTHERSQL_RESOURCEENTRY_H

#include <vector>
#include <deque>
#include <ostream>
#include <mutex>


#include "Lock.h"
#include "LockRequest.h"
#include "_macro.h"
#include <functional>

class LockManager;

class ResourceEntry {
private:
    std::reference_wrapper<LockManager> _lockManager;
    std::vector<Lock> locks;
    std::deque<LockRequest> waitingQueue;

    void processQueue(const TransactionContext &transaction, const std::unique_lock<std::mutex> &_lockManagerGuard);

    friend class LockManager;
public:
    ResourceEntry(LockManager &lockManager);

    bool checkCompatible(LockType lt, i64 except);

    void grantOrUpdateLock(Lock lock);

    void releaseLock(Lock lock, const TransactionContext &transaction,
                     const std::unique_lock<std::mutex> &_lockManagerGuard);

    void addToQueue(LockRequest request, bool addFront);

    LockType getTransactionLockType(i64 transaction);

    friend std::ostream &operator<<(std::ostream &os, const ResourceEntry &entry);
};


#endif //ANOTHERSQL_RESOURCEENTRY_H
