#ifndef ANOTHERSQL_BPLUSNODE_H
#define ANOTHERSQL_BPLUSNODE_H

#include <memory>
#include <optional>
#include <fstream>

#include "storage/Page.h"
#include "storage/DataBox.h"
#include "storage/RecordId.h"
#include "_macro.h"

class LeafNode;
class BPlusTreeMetadata;

class BPlusNode : public Page { ;
protected:
    BPlusNode(BufferManager& bufferManager,LockContext& lc): Page(lc,bufferManager){}

public:

    virtual std::shared_ptr<BPlusNode> get(DataBox key) = 0;

    virtual std::shared_ptr<BPlusNode> getLeftmostLeaf() = 0;

    virtual std::optional<std::pair<DataBox, i64>> insert(DataBox key, RecordId rid) = 0;

    virtual void erase(const DataBox& key) = 0;

    static std::shared_ptr<BPlusNode> fromBinary(std::ifstream &inFile,const BPlusTreeMetadata& metadata,const BufferManager& bufferManager);
};


#endif //ANOTHERSQL_BPLUSNODE_H
