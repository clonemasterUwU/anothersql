
#include "recovery/RecoveryManager.h"
#include "io/DiskSpaceManager.h"
#include "memory/BufferManager.h"
void RecoveryManager::setManagers(DiskSpaceManager &diskSpaceManager, BufferManager &bufferManager) {
    _diskSpaceManager = std::experimental::make_observer(&diskSpaceManager);
    _bufferManager = std::experimental::make_observer(&bufferManager);
}
