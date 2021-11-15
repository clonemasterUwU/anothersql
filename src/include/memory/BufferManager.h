#ifndef ANOTHERSQL_BUFFERMANAGER_H
#define ANOTHERSQL_BUFFERMANAGER_H


#include <condition_variable>
#include <unordered_map>
#include <mutex>
#include <vector>
#include "recovery/LogManager.h"
#include "io/DiskSpaceManager.h"
#include "Page.h"
#include "Frame.h"

class ClockEvictionPolicy;

class BufferManager {
private:
    i32 firstFreeIndex;
    DiskSpaceManager &diskSpaceManager;
    ClockEvictionPolicy &evictionPolicy;
    std::unordered_map<i64, u32> pageToFrame;
    std::vector<std::shared_ptr<Frame>> frames;
    std::condition_variable hasFreePage;
    std::mutex managerLock;

    friend class Frame;

public:
    BufferManager(DiskSpaceManager &diskSpaceManager, ClockEvictionPolicy &clockEvictionPolicy) :
            evictionPolicy(clockEvictionPolicy), diskSpaceManager(diskSpaceManager) {};

    static i32 RESERVED_SPACE;
    static i32 EFFECTIVE_PAGE_SIZE;

    Frame &fetchPageFrame(i64 pageNum);

    ~BufferManager();
};


#endif //ANOTHERSQL_BUFFERMANAGER_H
