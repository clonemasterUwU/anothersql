
#ifndef ANOTHERSQL_RECOVERYMANAGER_H
#define ANOTHERSQL_RECOVERYMANAGER_H

#include <experimental/memory>
class DiskSpaceManager;
class BufferManager;
class RecoveryManager {
private:
    std::experimental::observer_ptr<DiskSpaceManager> _diskSpaceManager;
    std::experimental::observer_ptr<BufferManager> _bufferManager;
public:
    RecoveryManager(){};
    void setManagers(DiskSpaceManager& diskSpaceManager,BufferManager& bufferManager);
};


#endif //ANOTHERSQL_RECOVERYMANAGER_H
