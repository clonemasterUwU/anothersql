#ifndef ANOTHERSQL_FRAME_H
#define ANOTHERSQL_FRAME_H

#include <memory>
#include <mutex>
#include <cstring>
#include <recovery/LogManager.h>
#include "_macro.h"
#include "sync/PinLock.h"
#include "sync/PinMutex.h"
#include "io/DiskSpaceManager.h"


class BufferManager;

class ClockEvictionPolicy;

class Frame {
private:
    enum tag {
        ACTIVE, INACTIVE,
    };

    friend class ClockEvictionPolicy;

    friend class BufferManager;

    tag tag;
    BufferManager &bufferManager;
    std::unique_ptr<u8[]> contents;
    i64 pageNum;
    bool dirty;
    i32 index;
    std::mutex frameLock;
    PinMutex pinMutex;
    bool logPage;
    static i32 INVALID_INDEX;

    void invalidate() {
        if (isValid()) {
            flush();
        }
        index = INVALID_INDEX;
        contents = nullptr;
    }

    void setFree();

    void setUsed();

    void flush();

    i32 dataOffset() const;

    void readBytes(i32 position, i32 num, u8 *buf);

public:

    Frame(BufferManager &bf, std::unique_ptr<u8[]> contents, i32 index, i64 pageNum) :
            bufferManager(bf), contents(std::move(contents)), pageNum(pageNum), index(index), dirty(false), logPage(
            DiskSpaceManager::getPartNum(pageNum) == LogManager::LOG_PARTITION), tag(INACTIVE) {};

    Frame(BufferManager &bf, std::unique_ptr<u8[]> contents, i32 nextFree) :
            Frame(bf, std::move(contents), ~nextFree, DiskSpaceManager::INVALID_PAGE_NUM) {};

    void pin() {
        frameLock.lock();
        assert(isValid());
        pinMutex.pin();
    }

    void unpin() {
        pinMutex.unpin();
        frameLock.unlock();
    }

    bool isValid() const {
        return index >= 0;
    }

    bool isFreed() const {
        return index < 0 && index != INVALID_INDEX;
    }

    i64 getPageNum() const {
        return pageNum;
    };


    bool isPinned();
};


#endif //ANOTHERSQL_FRAME_H
