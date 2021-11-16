//
// Created by deal_with on 12/11/2021.
//

#include "memory/Frame.h"
#include "memory/BufferManager.h"
#include "memory/ClockEvictionPolicy.h"
i32 Frame::INVALID_INDEX = INT32_MIN;

void Frame::setFree() {
    assert(!isFreed());
    i32 nextFreeIndex = bufferManager.firstFreeIndex;
    bufferManager.firstFreeIndex = index;
    index = ~nextFreeIndex;
}

void Frame::setUsed() {
    assert(isFreed());
    i32 temp = bufferManager.firstFreeIndex;
    bufferManager.firstFreeIndex = ~index;
    index = temp;
}

void Frame::flush() {
    PinLock<Frame> pinGuard(*this);
    if (!isValid() || !dirty) return;
    bufferManager.diskSpaceManager.writePage(pageNum, contents.get());
    dirty = false;
}

void Frame::readBytes(i32 position, i32 num, u8 *buf) {
    PinLock<Frame> pinGuard(*this);
    assert(isValid());
    memcpy(buf,contents.get()+position+dataOffset(),num);
    bufferManager.evictionPolicy.hit(*this);
}

i32 Frame::dataOffset() const {
    return logPage ? 0 : BufferManager::RESERVED_SPACE;
}

bool Frame::isPinned() {
    return pinMutex.isPinned();
}

