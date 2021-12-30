#ifndef ANOTHERSQL_INNERNODE_H
#define ANOTHERSQL_INNERNODE_H

#include <vector>
#include "storage/DataBox.h"
#include "BPlusNode.h"
#include "_macro.h"

class BPlusTreeMetadata;

class BufferManager;

class InnerNode : public BPlusNode {
private:
    std::reference_wrapper<const BPlusTreeMetadata> _metadata;
    std::vector<DataBox> keys;
    std::vector<i64> children;


    std::shared_ptr<BPlusNode> getChild(size_t i);

    std::optional<std::pair<DataBox, i64>> splitNodeIfExceed();

public:
    InnerNode(std::ifstream &inFile, const BPlusTreeMetadata &metadata, BufferManager &bufferManager,
              LockContext &treeContext);

    std::shared_ptr<BPlusNode> get(DataBox key) override;

    std::shared_ptr<BPlusNode> getLeftmostLeaf() override;

    std::optional<std::pair<DataBox, i64>> insert(DataBox key, RecordId rid) override;

    void erase(const DataBox &key) override;


};


#endif //ANOTHERSQL_INNERNODE_H


