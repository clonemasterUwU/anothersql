#include <filesystem>
#include "Database.h"

Database::Database(std::string fileDir, u32 numMemoryPages, LockManager lockManager,
                   std::unique_ptr<EvictionPolicy> evictionPolicy) {
    _dbDir = std::move(fileDir);
    bool initialize;
    {
        auto path = std::filesystem::path(_dbDir);
        initialize = std::filesystem::exists(path);
        if (!initialize) {
            if (!std::filesystem::create_directory(path)) {
                throw std::runtime_error("failed to create directory " + _dbDir);
            }
        } else if (!std::filesystem::is_directory(path)) {
            throw std::runtime_error(_dbDir + " is not a directory");
        }
        initialize = initialize && !std::filesystem::is_empty(path);
    }
    _numTransactions = 0;
    _numMemoryPages = numMemoryPages;
    _recoveryManager = RecoveryManager();
    _diskSpaceManager = DiskSpaceManager();
}
