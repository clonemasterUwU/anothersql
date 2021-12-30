#include "concurrency/LockRequest.h"

LockRequest::LockRequest(const TransactionContext &transaction, Lock lock, std::vector<Lock> releasedLock) :
        transaction(transaction), lock(lock), releaseLocks(std::move(releasedLock)) {}
