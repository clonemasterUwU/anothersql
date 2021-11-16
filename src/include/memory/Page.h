#ifndef ANOTHERSQL_PAGE_H
#define ANOTHERSQL_PAGE_H

#include "Frame.h"
class LockContext;
class Page {
private:
    LockContext& lockContext;
    std::shared_ptr<Frame> frame;
public:
    Page(LockContext& lockContext,std::shared_ptr<Frame> frame):lockContext(lockContext),frame(std::move(frame)){

    }
};


#endif //ANOTHERSQL_PAGE_H
