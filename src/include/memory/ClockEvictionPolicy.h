#ifndef ANOTHERSQL_CLOCKEVICTIONPOLICY_H
#define ANOTHERSQL_CLOCKEVICTIONPOLICY_H

#include <memory>
#include "_macro.h"
#include "EvictionPolicy.h"

class ClockEvictionPolicy : public EvictionPolicy {
private:
    u32 arm{0};
public:

};


#endif //ANOTHERSQL_CLOCKEVICTIONPOLICY_H
