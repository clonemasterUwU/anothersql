#include <cassert>
#include "index/LeafNode.h"
#include "index/BPlusTreeMetadata.h"

std::shared_ptr<BPlusNode> LeafNode::get(DataBox key) {
    return nullptr;
}

std::shared_ptr<BPlusNode> LeafNode::getLeftmostLeaf() {
    return nullptr;
}

std::optional<std::pair<DataBox, i64>> LeafNode::insert(DataBox key, RecordId rid) {
    auto maxOrder  =metadata.get().getLeafOrder();
    assert(keys.size() <=  maxOrder* 2);
    if(keys.size() == maxOrder * 2){
        std::vector<DataBox> newKeys(keys.begin()+maxOrder-1)
    }
}

void LeafNode::erase(const DataBox &key) {
    auto idx = std::lower_bound(keys.begin(), keys.end(), key) - keys.begin();
    if (idx != keys.size() && keys[idx] == key) {
        keys.erase(keys.begin() + idx);
        rids.erase(rids.begin() + idx);
    }
}

std::optional<RecordId> LeafNode::getKey(const DataBox &key) {
    auto idx = std::lower_bound(keys.begin(), keys.end(), key) - keys.begin();
    return idx != keys.size() && keys[idx] == key ? std::make_optional(rids[idx]) : std::nullopt;
}
