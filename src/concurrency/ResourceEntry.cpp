#include "concurrency/ResourceEntry.h"
#include "parallelism/TransactionContext.h"
#include "concurrency/LockManager.h"
#include <cassert>

void ResourceEntry::processQueue(const TransactionContext &transaction,
                                 const std::unique_lock<std::mutex> &_lockManagerGuard) {
    while (!waitingQueue.empty() &&
           checkCompatible(waitingQueue.front().lock.lt, waitingQueue.front().transaction.getTransNum())) {
        LockRequest lr = std::move(waitingQueue.front());
        waitingQueue.pop_front();
        grantOrUpdateLock(Lock(lr.lock._resourceName, lr.lock.lt, lr.transaction.getTransNum()));
        for (auto &releaseLock: lr.releaseLocks) {
            _lockManager.get()._release(transaction, releaseLock._resourceName, _lockManagerGuard);
        }
        lr.transaction._goodToGo.notify_one();
    }
}

bool ResourceEntry::checkCompatible(LockType lt, i64 except) {
    for (auto &current: locks) {
        if (current.transactionNum == except) continue;
        if (!LT::compatible(lt, current.lt)) return false;
    }
    return true;
}

void ResourceEntry::grantOrUpdateLock(Lock lock) {
    for (auto &current: locks) {
        if (current.transactionNum == lock.transactionNum) {
            for (auto &l: _lockManager.get().transactionLocks.find(lock.transactionNum)->second) {
                if (l == current) {
                    l.lt = lock.lt;
                    current.lt = lock.lt;
                    return;
                }
            }
            assert(false);
        }
    }
    locks.push_back(lock);
    _lockManager.get().transactionLocks[lock.transactionNum].push_back(lock);
}

void ResourceEntry::releaseLock(Lock lock, const TransactionContext &transaction,
                                const std::unique_lock<std::mutex> &_lockManagerGuard) {
    locks.erase(std::find(locks.begin(), locks.end(), lock));
    auto found = _lockManager.get().transactionLocks.erase(lock.transactionNum);
    assert(found);
    return processQueue(transaction, std::move(_lockManagerGuard));
}

void ResourceEntry::addToQueue(LockRequest request, bool addFront) {
    if (addFront) {
        waitingQueue.push_front(std::move(request));
    } else {
        waitingQueue.push_back(std::move(request));
    }
}

LockType ResourceEntry::getTransactionLockType(i64 transaction) {
    for (auto &current: locks) {
        if (current.transactionNum == transaction) {
            return current.lt;
        }
    }
    return NL;
}

ResourceEntry::ResourceEntry(LockManager &lockManager) : _lockManager(lockManager) {

}

std::ostream &operator<<(std::ostream &os, const ResourceEntry &entry) {
    os << "Active Locks: " << entry.locks << " waitingQueue: " << entry.waitingQueue;
    return os;
}
