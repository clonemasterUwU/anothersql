#include <cassert>
#include "index/InnerNode.h"
#include "memory/BufferManager.h"
#include "index/BPlusTreeMetadata.h"

std::shared_ptr<BPlusNode> InnerNode::get(DataBox key) {
    size_t i = 0;
    while (i < keys.size() && key >= keys[i]) {
        i++;
    }
    return getChild(i);
}

std::shared_ptr<BPlusNode> InnerNode::getLeftmostLeaf() {
    return getChild(0);
}

std::optional<std::pair<DataBox, i64>> InnerNode::insert(DataBox key, RecordId rid) {
    size_t i = 0;
    while (i < keys.size() && key >= keys[i]) i++;
    auto result = getChild(i)->insert(key, rid);
    if (result.has_value()) {
        keys.push_back(result->first);
        children.push_back(result->second);
        return splitNodeIfExceed();
    } else {
        return std::nullopt;
    }
}

void InnerNode::erase(const DataBox &key) {
    size_t i = 0;
    while (i < keys.size() && key >= keys[i]) i++;
    getChild(i)->erase(key);
}

std::optional<std::pair<DataBox, i64>> InnerNode::splitNodeIfExceed() {
    auto maxOrder = _metadata.get().getInnerOrder();
    if (keys.size() > 2 * maxOrder) {
        assert(keys.size() == 2 * maxOrder + 1);
        std::vector<DataBox> newKeys{keys.begin() + maxOrder + 1, keys.end()};
        std::vector<i64> nextChildren{children.begin() + maxOrder + 1, children.end()};
        auto keyUp = keys[maxOrder];
        keys.erase(keys.begin() + maxOrder, keys.end());
        children.erase(children.begin() + maxOrder + 1, children.end());
    }
    return std::nullopt;
}

std::shared_ptr<BPlusNode> InnerNode::getChild(size_t i) {
    auto pageNum = children[i];
}

InnerNode::InnerNode(std::ifstream &inFile, const BPlusTreeMetadata &metadata, BufferManager &bufferManager,
                     LockContext &treeContext) :
        BPlusNode(bufferManager, treeContext), _metadata(metadata) {
    u32 n;
    i64 temp;
    inFile.read((char *) (&n), sizeof n);
    keys.reserve(n);
    children.reserve(n + 1);
    for (u32 i = 0; i < n; i++) keys.push_back(::fromBinary(inFile, metadata.getKeyIndex()));
    for (u32 i = 0; i < n + 1; i++) {
        inFile.read((char *) &temp, sizeof(i64));
        children.push_back(temp);
    }
    _lockContext.
}
