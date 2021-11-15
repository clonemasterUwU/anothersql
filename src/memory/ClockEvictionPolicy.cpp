//
// Created by deal_with on 12/11/2021.
//
#include "memory/ClockEvictionPolicy.h"
#include "memory/Frame.h"

void ClockEvictionPolicy::hit(Frame &frame) {
    frame.tag = Frame::ACTIVE;
}

Frame *ClockEvictionPolicy::evict(std::vector<std::shared_ptr<Frame>> &frames) {
    u32 iters = 0;
    while ((frames[arm]->tag == Frame::ACTIVE || frames[arm]->isPinned()) && iters < 2 * frames.size()) {
        frames[arm]->tag = Frame::INACTIVE;
        arm = (arm + 1) % frames.size();
        iters++;
    }
    if (iters == 2 * frames.size()) return nullptr;
    Frame *evicted = frames[arm].get();
    arm = (arm + 1) % frames.size();
    return evicted;
}
