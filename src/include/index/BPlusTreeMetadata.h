
#ifndef ANOTHERSQL_BPLUSTREEMETADATA_H
#define ANOTHERSQL_BPLUSTREEMETADATA_H

#include "_macro.h"
class BPlusTreeMetadata {
private:
    i32 innerOrder;
    i32 leafOrder;
public:
    inline i32 getInnerOrder() const;
    inline i32 getLeafOrder() const;
    inline u32 getKeyIndex() const;
};


#endif //ANOTHERSQL_BPLUSTREEMETADATA_H
