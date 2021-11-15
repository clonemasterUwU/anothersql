//
// Created by deal_with on 12/11/2021.
//

#ifndef ANOTHERSQL_PINMUTEX_H
#define ANOTHERSQL_PINMUTEX_H

#include <cassert>
#include "_macro.h"
class PinMutex {
private:
    i32 pinCount;
public:
    PinMutex() : pinCount(0) {};

    void pin() {
        pinCount++;
    }

    void unpin() {
        assert(isPinned());
        --pinCount;
    }

    bool isPinned() {
        return pinCount > 0;
    }
};


#endif //ANOTHERSQL_PINMUTEX_H
