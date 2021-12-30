#ifndef ANOTHERSQL_DATABASE_H
#define ANOTHERSQL_DATABASE_H

#include "storage/Table.h"
#include "memory/BufferManager.h"
#include "concurrency/LockManager.h"
#include "io/DiskSpaceManager.h"
#include "recovery/RecoveryManager.h"
class Database {
private:
    std::string _dbDir;
    Table _tableMetadata;
    Table _indexMetadata;
    BufferManager _bufferManager;
    LockManager _lockManager;
    DiskSpaceManager _diskSpaceManager;
    RecoveryManager _recoveryManager;
    u64 _numTransactions;
    u32 _numMemoryPages;
public:
    Database(std::string fileDir, u32 numMemoryPages, LockManager lockManager,
             std::unique_ptr<EvictionPolicy> evictionPolicy);
};


#endif //ANOTHERSQL_DATABASE_H
