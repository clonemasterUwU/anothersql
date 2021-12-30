#ifndef ANOTHERSQL_TRANSACTIONCONTEXT_H
#define ANOTHERSQL_TRANSACTIONCONTEXT_H

#include <mutex>
#include <condition_variable>
#include "_macro.h"

class TransactionContext {
private:
    std::condition_variable _goodToGo;

    friend class ResourceEntry;

    friend class LockManager;

public:

    i64 getTransNum() const;

};


#endif //ANOTHERSQL_TRANSACTIONCONTEXT_H
