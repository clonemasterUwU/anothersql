#ifndef ANOTHERSQL_LOCKMANAGER_H
#define ANOTHERSQL_LOCKMANAGER_H


#include <unordered_map>
#include <vector>
#include <mutex>
#include "_macro.h"
#include "Lock.h"
#include "ResourceName.h"
#include "ResourceEntry.h"

class LockManager {
private:
    std::mutex _lock;
    std::unordered_map<i64, std::vector<Lock>> transactionLocks;
    std::unordered_map<ResourceName,ResourceEntry,ResourceNameHash > resourceEntries;


    void _acquireAndRelease(TransactionContext &transaction, const ResourceName &resourceName, LockType lt,
                            std::vector<std::reference_wrapper<ResourceName>> &releaseNames, std::unique_lock<std::mutex>& _guard);

    void _release(const TransactionContext &transaction, const ResourceName &resourceName,
                  const std::unique_lock<std::mutex> &_guard);

    void _acquire(TransactionContext &transaction, const ResourceName &resourceName, LockType lt,
                  std::unique_lock<std::mutex> &_guard);

    void _promote(TransactionContext &transaction, const ResourceName &resourceName, LockType nlt,
                  std::unique_lock<std::mutex> &_guard);
    ResourceEntry& getResourceEntry(const ResourceName& name);

    friend class ResourceEntry;

public:
    void acquireAndRelease(const TransactionContext &transaction, const ResourceName &resourceName, LockType lt,
                           std::vector<ResourceName &> &releaseNames);

    void release(const TransactionContext &transaction, const ResourceName &resourceName);
};


#endif //ANOTHERSQL_LOCKMANAGER_H
