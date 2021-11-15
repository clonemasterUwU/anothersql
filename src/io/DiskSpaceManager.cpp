#include "io/DiskSpaceManager.h"
i64 DiskSpaceManager::INVALID_PAGE_NUM = -1L;
i32 DiskSpaceManager::PAGE_SIZE = 4096;

void DiskSpaceManager::writePage(i64 page,u8* buf) {
    //TODO
}

i32 DiskSpaceManager::getPartNum(i64) {
    //TODO
    return 0;
}

bool DiskSpaceManager::pageAllocated(i64 i) {
    //TODO
    return true;
}

void DiskSpaceManager::readPage(i64 page, u8 *buf) {
    //TODO;
}
