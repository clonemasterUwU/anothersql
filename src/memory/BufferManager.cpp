#include <cassert>

#include "memory/BufferManager.h"
#include "memory/Frame.h"
#include "memory/ClockEvictionPolicy.h"

i32 BufferManager::RESERVED_SPACE = 36;

i32 BufferManager::EFFECTIVE_PAGE_SIZE = DiskSpaceManager::PAGE_SIZE - RESERVED_SPACE;

Frame &BufferManager::fetchPageFrame(i64 pageNum) {
    std::unique_lock<std::mutex> managerGuard(managerLock), evictedGuard, newGuard;
    Frame *evictingFrame, *newFrame;
    std::shared_ptr<Frame> evictedFrame{nullptr};
    do {
        assert(diskSpaceManager.pageAllocated(pageNum));
        auto p = pageToFrame.find(pageNum);
        if (p != pageToFrame.end()) {
            Frame &res = *frames[p->second];
            res.pin();
            return res;
        }
        if (firstFreeIndex < frames.size()) {
            evictingFrame = frames[firstFreeIndex].get();
            evictingFrame->setUsed();
        } else {
            evictingFrame = evictionPolicy.evict(frames);
            if (evictingFrame) {
                pageToFrame.erase(evictingFrame->pageNum);
                evictionPolicy.cleanup(*evictingFrame);
                u32 frameIndex = evictingFrame->index;
                evictedFrame = std::move(frames[frameIndex]);
                newFrame = (frames[frameIndex] =
                                    std::make_shared<Frame>(evictedFrame->bufferManager,
                                                            std::move(evictedFrame->contents), frameIndex,
                                                            pageNum)).get();
                //yoink their buffer(content) anyway
                pageToFrame[pageNum] = frameIndex;
                evictedGuard = std::unique_lock<std::mutex>(evictedFrame->frameLock);
                newGuard = std::unique_lock<std::mutex>(newFrame->frameLock);
            } else {
                hasFreePage.wait(managerGuard);
            }
        }
    } while (!evictedFrame);
    managerGuard.unlock();
    evictedFrame->invalidate();
    evictedGuard.unlock();
    newFrame->pin();
    newFrame->bufferManager.diskSpaceManager.readPage(pageNum, newFrame->contents.get());
    newGuard.unlock();
    return *newFrame;
}

BufferManager::~BufferManager(){
    std::scoped_lock<std::mutex> managerGuard(managerLock);
    //
}
