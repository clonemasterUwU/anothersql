//
// Created by deal_with on 11/11/2021.
//

#ifndef ANOTHERSQL_DISKSPACEMANAGER_H
#define ANOTHERSQL_DISKSPACEMANAGER_H
#include <memory>
#include "_macro.h"
class DiskSpaceManager {
private:
    friend class BufferManager;
public:
    static i64 INVALID_PAGE_NUM;
    static i32 PAGE_SIZE;
    void writePage(i64 page,u8* buf);
    void readPage(i64 page,u8* buf);
    static i32 getPartNum(i64);

    bool pageAllocated(i64 i);
};


#endif //ANOTHERSQL_DISKSPACEMANAGER_H
