#include <cassert>
#include "concurrency/LockManager.h"
#include "parallelism/TransactionContext.h"

void LockManager::_release(const TransactionContext &transaction, const ResourceName &resourceName,
                           const std::unique_lock<std::mutex> &_guard) {
    auto &resourceEntry = getResourceEntry(resourceName);
    auto lt = resourceEntry.getTransactionLockType(transaction.getTransNum());
    assert(lt != NL);
    resourceEntry.releaseLock(Lock(resourceName, lt, transaction.getTransNum()), transaction, _guard);
}

void LockManager::_acquireAndRelease(TransactionContext &transaction, const ResourceName &resourceName, LockType lt,
                                     std::vector<std::reference_wrapper<ResourceName>> &releaseNames,
                                     std::unique_lock<std::mutex> &_guard) {
    ResourceEntry &resourceEntry = getResourceEntry(resourceName);
    assert(resourceEntry.getTransactionLockType(transaction.getTransNum()) != lt);
    std::vector<LockType> lockTypes;
    lockTypes.reserve(releaseNames.size());
    for (auto &releaseName: releaseNames) {
        LockType rlt = getResourceEntry(releaseName).getTransactionLockType(transaction.getTransNum());
        assert(rlt != NL);
        lockTypes.push_back(rlt);
    }
    if (resourceEntry.checkCompatible(lt, transaction.getTransNum())) {
        resourceEntry.grantOrUpdateLock(Lock(resourceName, lt, transaction.getTransNum()));
        for (std::size_t i = 0; i < releaseNames.size(); i++) {
            if (releaseNames[i] == resourceName) continue;
            getResourceEntry(releaseNames[i]).releaseLock(
                    Lock(releaseNames[i], lockTypes[i], transaction.getTransNum()), transaction, _guard);
        }
    } else {
        std::vector<Lock> release;
        release.reserve(releaseNames.size());
        for (std::size_t i = 0; i < releaseNames.size(); i++) {
            release.emplace_back(releaseNames[i], lockTypes[i], transaction.getTransNum());
        }
        resourceEntry.addToQueue(
                LockRequest(transaction, Lock(resourceName, lt, transaction.getTransNum()), std::move(release)), true);
        transaction._goodToGo.wait(_guard);
    }
}

ResourceEntry &LockManager::getResourceEntry(const ResourceName &name) {
    if (!resourceEntries.count(name)) {
        resourceEntries.emplace(name, ResourceEntry(*this));
    }
    return resourceEntries.find(name)->second;

}

void LockManager::_acquire(TransactionContext &transaction, const ResourceName &resourceName, LockType lt,
                           std::unique_lock<std::mutex> &_guard) {
    auto &resourceEntry = getResourceEntry(resourceName);
    assert(resourceEntry.getTransactionLockType(transaction.getTransNum()) != lt);
    if (resourceEntry.waitingQueue.empty() && resourceEntry.checkCompatible(lt, transaction.getTransNum())) {
        resourceEntry.grantOrUpdateLock(Lock(resourceName, lt, transaction.getTransNum()));
    } else {
        resourceEntry.addToQueue(LockRequest(transaction, Lock(resourceName, lt, transaction.getTransNum())), false);
        transaction._goodToGo.wait(_guard);
    }
}

void LockManager::_promote(TransactionContext &transaction, const ResourceName &resourceName, LockType nlt,
                           std::unique_lock<std::mutex> &_guard) {
    ResourceEntry &resourceEntry = getResourceEntry(resourceName);
    LockType olt = resourceEntry.getTransactionLockType(transaction.getTransNum());
    assert(olt != nlt && LT::substitutable(nlt, olt));
    if (resourceEntry.checkCompatible(nlt, transaction.getTransNum())) {
        for (auto &lock: resourceEntry.locks) {
            if (lock.transactionNum == transaction.getTransNum()) {
                lock.lt = nlt;
                return;
            }
        }
        assert(false);
    } else {
        resourceEntry.addToQueue(LockRequest(transaction, Lock(resourceName, nlt, transaction.getTransNum())), true);
        transaction._goodToGo.wait(_guard);
    }
}
