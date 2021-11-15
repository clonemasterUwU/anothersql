#ifndef ANOTHERSQL_RW_LATCH_MUTEX_H
#define ANOTHERSQL_RW_LATCH_MUTEX_H

#include <mutex>
#include <condition_variable>

#include "sync/rw_latch_base.h"
#include "_macro.h"

class rw_latch_mutex : public rw_latch_base {
private:
    u32 _reader_count, _writer_count, _writer_wait;
    std::mutex _mutex;
    std::condition_variable _reader, _writer;
public:
    rw_latch_mutex();

    ~rw_latch_mutex() = default;


    void lock_shared() override;

    void lock() override;

    void unlock_shared() override;

    void unlock() override;
};


#endif //ANOTHERSQL_RW_LATCH_MUTEX_H
