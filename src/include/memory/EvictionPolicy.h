//
// Created by deal_with on 12/11/2021.
//

#ifndef ANOTHERSQL_EVICTIONPOLICY_H
#define ANOTHERSQL_EVICTIONPOLICY_H

#include <vector>
#include <memory>
class Frame;
class EvictionPolicy {

public:

    virtual void init(Frame &) = 0;

    virtual void hit(Frame &) = 0;

    virtual Frame* evict(std::vector<std::unique_ptr<Frame>>&)=0;

    virtual void cleanup(Frame&)=0;
};


#endif //ANOTHERSQL_EVICTIONPOLICY_H
