
#ifndef ANOTHERSQL_LEAFNODE_H
#define ANOTHERSQL_LEAFNODE_H

#include <vector>
#include "BPlusNode.h"
#include "storage/DataBox.h"
#include "storage/RecordId.h"
class BPlusTreeMetadata;
class LeafNode: public BPlusNode{
public:
    std::shared_ptr<BPlusNode> get(DataBox key) override;

    std::shared_ptr<BPlusNode> getLeftmostLeaf() override;

    std::optional<std::pair<DataBox, i64>> insert(DataBox key, RecordId rid) override;

    void erase(const DataBox& key) override;

    std::optional<RecordId> getKey(const DataBox& key);
private:
    std::reference_wrapper<BPlusTreeMetadata> metadata;
    std::vector<DataBox > keys;
    std::vector<RecordId> rids;
};


#endif //ANOTHERSQL_LEAFNODE_H
