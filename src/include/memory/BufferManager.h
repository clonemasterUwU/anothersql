#ifndef ANOTHERSQL_BUFFERMANAGER_H
#define ANOTHERSQL_BUFFERMANAGER_H


#include <condition_variable>
#include <unordered_map>
#include <mutex>
#include <vector>
#include "_macro.h"

#include "Page.h"
#include "EvictionPolicy.h"
class DiskSpaceManager;
class BufferManager {
private:
    i32 firstFreeIndex;
    std::reference_wrapper<DiskSpaceManager> _diskSpaceManager;
    std::unique_ptr<EvictionPolicy> _evictionPolicy;
    std::unordered_map<i64, u32> pageToFrame;
    std::condition_variable hasFreePage;
    std::mutex managerLock;



public:
    BufferManager(DiskSpaceManager &diskSpaceManager, std::unique_ptr<EvictionPolicy> evictionPolicy) :
            _evictionPolicy(std::move(evictionPolicy)), _diskSpaceManager(diskSpaceManager) {};

    static i32 RESERVED_SPACE;
    static i32 EFFECTIVE_PAGE_SIZE;


    ~BufferManager();
};


#endif //ANOTHERSQL_BUFFERMANAGER_H
