
#ifndef ANOTHERSQL_RECORDID_H
#define ANOTHERSQL_RECORDID_H

#include "_macro.h"
class RecordId {
private:
    i64 _pageNum;
    i32 _entryNum;
public:
    RecordId(i64 pageNum,i32 entryNum):_pageNum(pageNum),_entryNum(entryNum){};
};


#endif //ANOTHERSQL_RECORDID_H
