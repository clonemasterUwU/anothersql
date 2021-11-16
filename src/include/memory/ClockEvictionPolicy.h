
#ifndef ANOTHERSQL_CLOCKEVICTIONPOLICY_H
#define ANOTHERSQL_CLOCKEVICTIONPOLICY_H

#include <memory>
#include "_macro.h"
#include "EvictionPolicy.h"
#include "Frame.h"

class ClockEvictionPolicy : public EvictionPolicy {
private:
    u32 arm{0};
public:
    void init(Frame &frame) override {

    }

    void hit(Frame &frame) override;

    Frame *evict(std::vector<std::shared_ptr<Frame>> &frames) override;

    void cleanup(Frame &frame) override {

    }
};


#endif //ANOTHERSQL_CLOCKEVICTIONPOLICY_H
