#include <cassert>

#include "index/BPlusNode.h"
#include "index/InnerNode.h"
#include "index/LeafNode.h"
std::shared_ptr<BPlusNode> fromBinary(std::ifstream &inFile,const BPlusTreeMetadata& metadata,BufferManager& bufferManager,LockContext& treeContext){
    u8 nodeType;
    inFile.read((char*)&nodeType, sizeof nodeType);
    if(nodeType==0){
        return std::make_shared<InnerNode>(inFile,metadata,bufferManager,treeContext);
    } else {
        assert(nodeType==1);
        return std::make_shared<LeafNode>()
    }
}
